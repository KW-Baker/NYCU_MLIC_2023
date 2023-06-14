/***************************************************************************************************/
// FILE NAME:    FSM.cpp
// VERSION:      1.0 
// DATE:         Jun 11, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Final Project
// MODIFICATION: 
// Date          Description
// 06/11        
/***************************************************************************************************/
#include "FSM.h"
#include "cmath"
using namespace std;


void FSM::run() {
	// vvvvv put your code here vvvvv
	if( rst ){
		rom_rd->nb_write( false );
		rom_addr->nb_write( 0 );
		data_out_signal->nb_write( false );
		data_out->nb_write( 0 );
		state = S_IDLE;
		cnt = 0;
		tmp_cnt = 0;
		addr = 0;
		channel = 0;
		row  = 0;
		col  = 0;
	}
	else{
		// IDLE
		if(state == S_IDLE){
			rom_rd->nb_write( false );
			rom_addr->nb_write( 0 );
			data_out_signal->nb_write( false );
			data_out->nb_write( 0 );
			state = S_LOAD_IMG;
			cnt  = 0;
			tmp_cnt = 0;
			addr = 0;
			channel = 0;
			row  = 0;
			col  = 0;	
		}

		// LOAD IMAGE
		else if(state == S_LOAD_IMG){
			rom_rd->nb_write( true );
			rom_addr->nb_write( cnt );
			data_out_signal->nb_write( false );
			data_out->nb_write( 0 );

			// Read image 1
			if( cnt >= offset &&
			    cnt < IMG_SIZE*IMG_SIZE + offset){
				addr = cnt - offset;
				row = addr / IMG_SIZE;
				col = addr % IMG_SIZE;
				data_in->nb_read( img[0][row][col] );
			}

			// Read image 2
			else if( (cnt >= IMG_SIZE*IMG_SIZE + offset) &&
			         (cnt < IMG_NUM*IMG_SIZE*IMG_SIZE + offset) ){
				addr = cnt - offset;
				row = ( addr - IMG_SIZE*IMG_SIZE ) / IMG_SIZE;
				col = ( addr - IMG_SIZE*IMG_SIZE ) % IMG_SIZE;
				data_in->nb_read( img[1][row][col] );
			}
			cnt++;

			if(cnt == IMG_NUM*IMG_SIZE*IMG_SIZE + offset)
				state = S_LOAD_LAYER1;
		}

		// LOAD LAYER1
		else if(state == S_LOAD_LAYER1){
			rom_rd->nb_write( true );
			rom_addr->nb_write( cnt );
			data_out_signal->nb_write( false );
			data_out->nb_write( 0 );

			// Read Conv weights
			if( (cnt >= IMG_NUM*IMG_SIZE*IMG_SIZE + offset) &&
			    (cnt < IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + offset) ){
				addr = cnt - offset;
				channel = ( addr - IMG_NUM*IMG_SIZE*IMG_SIZE ) / ( KER_SIZE*KER_SIZE );
				row = ( addr - IMG_NUM*IMG_SIZE*IMG_SIZE - channel*KER_SIZE*KER_SIZE ) / KER_SIZE;
				col = ( addr - IMG_NUM*IMG_SIZE*IMG_SIZE - channel*KER_SIZE*KER_SIZE ) % KER_SIZE;
				data_in->nb_read( conv_weight[channel][row][col] );
			}

			// Read Conv biases
			else if( (cnt >= IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + offset) &&
			         (cnt < IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE + offset) ){
				addr = cnt - offset;
				channel = 0;
				row = 0;
				col = 0;
				data_in->nb_read( conv_bias[tmp_cnt] );
				tmp_cnt++;
			}
			cnt++;

			if(cnt == IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE + offset)
				state = S_CONV1;
		}

		// CONV1
		else if(state == S_CONV1){
			rom_rd->nb_write( false );
			//// image 1  //// 
			// Convolution
			for(auto c = 0; c < CH1_SIZE; ++c){
				for(auto i = 0; i < FMAP_SIZE; ++i){
					for(auto j = 0; j < FMAP_SIZE; ++j){
						sum = 0;
						for(auto ki = 0; ki < KER_SIZE; ++ki){ 
							for(auto kj = 0; kj < KER_SIZE; ++kj){
								sum += img[0][i+ki][j+kj] * conv_weight[c][ki][kj];
							}
						}
						// ReLU
						conv1_fmap[0][c][i][j] = ( (sum + conv_bias[c]) > 0 ) ? sum + conv_bias[c] : 0;
					}
				}
			}

			//// image 2  //// 
			// Convolution
			for(auto c = 0; c < CH1_SIZE; ++c){
				for(auto i = 0; i < FMAP_SIZE; ++i){
					for(auto j = 0; j < FMAP_SIZE; ++j){
						sum = 0;
						for(auto ki = 0; ki < KER_SIZE; ++ki){ 
							for(auto kj = 0; kj < KER_SIZE; ++kj){
								sum += img[1][i+ki][j+kj] * conv_weight[c][ki][kj];
							}
						}
						// ReLU
						conv1_fmap[1][c][i][j] = ( (sum + conv_bias[c]) > 0 ) ? sum + conv_bias[c] : 0;
					}
				}
			}
			state = S_POOL1;
		}

		// MAXPOO1
		else if (state == S_POOL1){
			//// image 1 ////
			for(auto c = 0; c < CH1_SIZE; ++c ){
				for(auto i = 0; i < PFMAP_SIZE; ++i){
					for(auto j = 0; j < PFMAP_SIZE; ++j){
						float max_val = 0;
						for(auto ki = 0; ki < POOL_SIZE; ++ki){
							for(auto kj = 0; kj < POOL_SIZE; ++kj){
								row = i * 2 + ki;
								col = j * 2 + kj;
								max_val = max(max_val, conv1_fmap[0][c][row][col]);
							}
						}
						pool1_fmap[0][c][i][j] = max_val;
					}
				}
			}

			//// image 2 ////
			for(auto c = 0; c < CH1_SIZE; ++c ){
				for(auto i = 0; i < PFMAP_SIZE; ++i){
					for(auto j = 0; j < PFMAP_SIZE; ++j){
						float max_val = 0;
						for(auto ki = 0; ki < POOL_SIZE; ++ki){
							for(auto kj = 0; kj < POOL_SIZE; ++kj){
								row = i * 2 + ki;
								col = j * 2 + kj;
								max_val = max(max_val, conv1_fmap[1][c][row][col]);
							}
						}
						pool1_fmap[1][c][i][j] = max_val;
					}
				}
			}

			// flatten pool1_fmap[0]
			tmp_cnt = 0;
			for(auto c = 0; c < CH1_SIZE; ++c){
				for(auto i = 0; i < PFMAP_SIZE; ++i){
					for(auto j = 0; j < PFMAP_SIZE; ++j){
						flatten[0][tmp_cnt] = pool1_fmap[0][c][i][j];
						tmp_cnt++;
					}
				}
			}

			// flatten pool1_fmap[1]
			tmp_cnt = 0;
			for(auto c = 0; c < CH1_SIZE; ++c){
				for(auto i = 0; i < PFMAP_SIZE; ++i){
					for(auto j = 0; j < PFMAP_SIZE; ++j){
						flatten[1][tmp_cnt] = pool1_fmap[1][c][i][j];
						tmp_cnt++;

					}
				}
			}

			state = S_LOAD_FC;
			tmp_cnt = 0;
		}

		else if(state == S_LOAD_FC){
			rom_rd->nb_write( true );
			rom_addr->nb_write( cnt );
			data_out_signal->nb_write( false );
			data_out->nb_write( 0 );

			// Read fully connected weights
			if( (cnt >= IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE + offset) &&
			    (cnt < IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE + FC_IN_SIZE*FC_OUT_SIZE + offset)){
				addr = cnt - offset;
				row = (addr - (IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE)) / FC_IN_SIZE;
				col = (addr - (IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE)) % FC_IN_SIZE;
				data_in->nb_read( fc_weight[row][col] );
			}

			// Read fully connected biases
			else if( (cnt >= IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE + FC_IN_SIZE*FC_OUT_SIZE + offset) &&
					 (cnt < IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE + FC_IN_SIZE*FC_OUT_SIZE + FC_OUT_SIZE + offset)){
				addr = cnt - offset;
				row = 0;
				col = 0;
				data_in->nb_read( fc_bias[tmp_cnt] );
				tmp_cnt++;
			}
			cnt++;

			if(cnt == IMG_NUM*IMG_SIZE*IMG_SIZE + CH1_SIZE*KER_SIZE*KER_SIZE + BIAS_SIZE + FC_IN_SIZE*FC_OUT_SIZE + FC_OUT_SIZE + offset)
				state = S_FC;
		}
		else if(state == S_FC){
			// PE0 ~ 15
			for(auto p = 0; p < PE_NUM; ++p){
				for(auto i = 0; i < FC_IN_SIZE; ++i){
					// image1
					result[0][p] += fc_weight[p][i]*flatten[0][i];

					// image2
					result[1][p] += fc_weight[p][i]*flatten[1][i];
				}
				result[0][p] += fc_bias[p];
				result[0][p] = 1 / (1 + exp(-result[0][p])); // sigmoid


				result[1][p] += fc_bias[p];
				result[1][p] = 1 / (1 + exp(-result[1][p])); // sigmoid
			}
			state = S_L1_DIST;
		}
		else if(state == S_L1_DIST){
			for(auto i = 0; i < FC_OUT_SIZE; ++i)
				output += abs( result[0][i] -  result[1][i]);
			
			output = 1 / (1 + exp(-output)); // Sigmoid

			cout << "Dissimilarity: "<< output << endl;
			if(output > THRESHOLD)
				cout << "Predict: Different" << endl;
			else
				cout << "Predict: Same" << endl;
			
			state = S_OUT;
		}
	}

}