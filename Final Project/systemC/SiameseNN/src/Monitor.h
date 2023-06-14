/***************************************************************************************************/
// FILE NAME:    Monitor.h
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

using namespace std;

SC_MODULE( Monitor ) {
	sc_in < bool > rst;
	sc_in_clk clk;
	sc_port< sc_fifo_in_if< sc_int<19> > > data_in;
	sc_port< sc_fifo_in_if < bool > > data_in_signal;

	void monitor();
	int x, y;
	
	SC_CTOR( Monitor )
	{	
		SC_METHOD( monitor );
		sensitive << rst.pos() << clk.pos();
	}
};
