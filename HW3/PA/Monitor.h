/***************************************************************************************************/
// FILE NAME:    Monitor.h
// VERSION:      1.0 
// DATE:         MAY 01, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Homework3 / CNN (PA)
// MODIFICATION: 
// Date          Description
// 05/28        
/***************************************************************************************************/
#include "systemc.h"
#include <iostream>

using namespace std;

SC_MODULE( Monitor ) {
	sc_in < bool > rst;
	sc_in_clk clk;
	sc_in< sc_int<19> >  data_in;
	sc_in< bool > data_in_signal;

	void monitor();
	int x, y;
	
	SC_CTOR( Monitor )
	{	
		SC_METHOD( monitor );
		sensitive << rst.pos() << clk.pos();
	}
};
