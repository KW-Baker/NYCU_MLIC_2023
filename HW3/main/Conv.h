/***************************************************************************************************/
// FILE NAME:    Conv.h
// VERSION:      1.0 
// DATE:         MAY 01, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Homework3 / CNN
// MODIFICATION: 
// Date          Description
// 05/28         
/***************************************************************************************************/
#include "systemc.h"
#include <iostream>
#include <fstream>

#define DEBUG     0
#define IMG_SIZE 10
#define KER_SIZE  3
#define FMAP_SIZE 8


using namespace std;

SC_MODULE( Conv ) {
	sc_in < bool > rst;
	sc_in_clk clk;
	sc_port< sc_fifo_out_if < bool > > rom_rd;
	sc_port< sc_fifo_out_if < sc_uint<7> > > rom_addr;
	sc_port< sc_fifo_in_if < float > > data_in;
	sc_port< sc_fifo_out_if < sc_int<19> > > data_out;
	sc_port< sc_fifo_out_if < bool > > data_out_signal;

	const int S_IDLE = 0;
	const int S_READ = 1;
	const int S_CONV = 2;
	const int S_OUT  = 3;

	const int offset = 3;

	
	bool debug = DEBUG;
	int state;
	int cnt;
	int addr;
	int row, col = 0;
	float img[IMG_SIZE][IMG_SIZE] = {0};
	float ker[KER_SIZE][KER_SIZE] = {0};
	float fmap[FMAP_SIZE][FMAP_SIZE] = {0};
	float bias;
	float sum;
	float output;

	
	void run();
	
    // vvvvv put your code here vvvvv

	
	// ^^^^^ put your code here ^^^^^

	SC_CTOR( Conv )
	{	
		SC_METHOD( run );
		sensitive << rst.pos() << clk.pos();
	}
};


