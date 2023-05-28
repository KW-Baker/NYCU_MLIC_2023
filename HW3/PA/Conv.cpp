/***************************************************************************************************/
// FILE NAME:    Conv.cpp
// VERSION:      1.0 
// DATE:         MAY 01, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Homework3 / CNN (PA)
// MODIFICATION: 
// Date          Description
// 05/28        
/***************************************************************************************************/
#include "Conv.h"


void Conv::run() {
	// vvvvv put your code here vvvvv
	if( rst ){
		rom_rd.write( false );
		rom_addr.write( 0 );
		data_out_signal.write( false );
		data_out.write( 0 );
		state = S_IDLE;
		cnt = 0;
		addr = 0;
		row = 0;
		col = 0;
	}
	else{
		if(state == S_IDLE){
			rom_rd.write( false );
			rom_addr.write( 0 );
			data_out_signal.write( false );
			data_out.write( 0 );
			cnt = 0;
			addr = 0;
			row = 0;
			col = 0;
			state = S_READ;
		}
		// Read state
		else if(state == S_READ){
			rom_rd.write( true );
			rom_addr.write( cnt );
			data_out_signal.write( false );
			data_out.write( 0 );

			// Read image
			if( cnt >= offset && cnt < IMG_SIZE*IMG_SIZE + offset ){
				addr = cnt - offset;
				row = addr / IMG_SIZE;
				col = addr % IMG_SIZE;
				img[row][col] = data_in.read();
				if(debug)
					cout << "addr: " << addr << ", pixel["<< row << "][" << col << "]: " << img[row][col] << endl;
				
			}
			// Read kernel
			else if ( (cnt >= IMG_SIZE*IMG_SIZE + offset) && (cnt < IMG_SIZE*IMG_SIZE + KER_SIZE*KER_SIZE + offset) ){
				addr = cnt - offset;
				row = ( addr - IMG_SIZE*IMG_SIZE ) / KER_SIZE;
				col = ( addr - IMG_SIZE*IMG_SIZE ) % KER_SIZE;
				ker[row][col] = data_in.read();
				if(debug)
					cout << "addr: " << addr << ", weight["<< row << "][" << col << "]: " << ker[row][col] << endl;
			}
			// Read bias
			else if( cnt == IMG_SIZE*IMG_SIZE + KER_SIZE*KER_SIZE + offset ){
				addr = cnt - offset;
				row = 0;
				col = 0;
				bias = data_in.read();
				state =  S_CONV;
				if(debug)
					cout << "addr: " << addr << ", bias: " << bias << endl;
			}
			cnt++;
		}
		// Convolution + ReLU
		else if(state == S_CONV){
			rom_rd.write( false );
			cnt = 0;
			addr = 0;
			// Covolution
			for(auto i = 0; i < FMAP_SIZE; ++i){
				for(auto j = 0; j < FMAP_SIZE; ++j){
					sum = 0;
					for(auto ki = 0; ki < KER_SIZE; ++ki){
						for(auto kj = 0; kj < KER_SIZE; ++kj){
							sum += img[i+ki][j+kj] * ker[ki][kj];
						}
					}
					// ReLU
					fmap[i][j] = ( (sum + bias) > 0 ) ? sum + bias : 0;
				}
			}
			state = S_OUT;
		}
		// Output
		else if(state == S_OUT){
			rom_rd.write( false );
			row =  cnt / FMAP_SIZE;
			col =  cnt % FMAP_SIZE;
			data_out_signal.write( true );
			data_out.write( fmap[row][col] );
			cnt++;
		}		
	}
	// ^^^^^ put your code here ^^^^^
}