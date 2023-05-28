/***************************************************************************************************/
// FILE NAME:    ROM.h
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
#include <fstream>

using namespace std;

SC_MODULE( ROM ) {	
	sc_in_clk clk;
	sc_in < bool > rom_rd;
	sc_in < sc_uint<7> > rom_addr;
	sc_out < float > data;
	
	float rom_M[110];
	void read_data();
	ifstream fin;
	int temp;
	
	SC_CTOR( ROM )
	{
		// vvvvv change the path of input file here vvvvv
		fin.open( "/home/ML310510221/310510221_HW3/PA/input.txt", ios::in );
		for ( int i = 0 ; i < 110 ; i++ )
			fin >> rom_M[i];
			
		fin.close();
		
		// SC_METHOD( read_data );
		SC_METHOD( read_data );
		sensitive << clk.pos();
	}
};


