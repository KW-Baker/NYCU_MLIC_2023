/***************************************************************************************************/
// FILE NAME:    FSM.h
// VERSION:      1.0 
// DATE:         June 11, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Final Project
// MODIFICATION: 
// Date          Description
// 06/11         
/***************************************************************************************************/
#include "systemc.h"
#include <iostream>
#include <fstream>

#define IMG_NUM        2
#define PE_NUM        16
#define IMG_SIZE      32
#define CH1_SIZE      32
#define CH2_SIZE    1024
#define KER_SIZE       3
#define POOL_SIZE      2
#define BIAS_SIZE     32
#define FMAP_SIZE     30
#define PFMAP_SIZE    15
#define FC_IN_SIZE  7200
#define FC_OUT_SIZE   16
#define THRESHOLD    0.9

using namespace std;

const int S_IDLE        = 0;
const int S_LOAD_IMG    = 1;
const int S_LOAD_LAYER1 = 2;
const int S_CONV1       = 3;
const int S_POOL1       = 4;
const int S_LOAD_FC     = 5;
const int S_FC          = 6;
const int S_L1_DIST     = 7;
const int S_OUT         = 8;

const int offset = 3;


SC_MODULE( FSM ) {
	sc_in < bool > rst;
	sc_in_clk clk;
	sc_port< sc_fifo_out_if < bool > > rom_rd;
	sc_port< sc_fifo_out_if < sc_uint<31> > > rom_addr;
	sc_port< sc_fifo_in_if < float > > data_in;
	sc_port< sc_fifo_out_if < sc_int<19> > > data_out;
	sc_port< sc_fifo_out_if < bool > > data_out_signal;

	int state;
	int cnt;
	int tmp_cnt;
	int addr;
	int channel, row, col = 0;

	// input images
	float img[IMG_NUM][IMG_SIZE][IMG_SIZE] = {0};
	
	// activations
	float conv1_fmap[IMG_NUM][CH1_SIZE][FMAP_SIZE][FMAP_SIZE]   = {0};
	float pool1_fmap[IMG_NUM][CH1_SIZE][PFMAP_SIZE][PFMAP_SIZE] = {0};
	float flatten[IMG_NUM][FC_IN_SIZE] = {0};

	// weights
	float conv_weight[CH1_SIZE][KER_SIZE][KER_SIZE] = {0};
	float conv_bias[CH1_SIZE] = {0};
	float fc_weight[FC_OUT_SIZE][FC_IN_SIZE] = {0};
	float fc_bias[FC_OUT_SIZE] = {0};
	float result[IMG_NUM][FC_OUT_SIZE] = {0};

	// output score
	float output;

	float sum;
	
	void run();
	
	SC_CTOR( FSM )
	{	
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};


