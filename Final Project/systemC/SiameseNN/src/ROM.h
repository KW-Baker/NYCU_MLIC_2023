/***************************************************************************************************/
// FILE NAME:    ROM.h
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

#define ROM_IMG_SIZE      2048
#define ROM_WEIGHT_SIZE 115536


using namespace std;

SC_MODULE( ROM ) {	
	sc_in_clk clk;
	sc_port< sc_fifo_in_if < bool > > rom_rd;
	sc_port< sc_fifo_in_if < sc_uint<31> > > rom_addr;
	sc_port< sc_fifo_out_if < float > > data;
	

	float rom_M[ ROM_IMG_SIZE + ROM_WEIGHT_SIZE ];
	void read_data();
	ifstream fin1;
	ifstream fin2;

	
	SC_CTOR( ROM )
	{
		cout << "[1] Loading input images..." << endl;
		fin1.open( "/home/ML310510221/Final_Project/SiameseNN/images/image1.txt", ios::in );
		for ( int i = 0 ; i < ROM_IMG_SIZE ; i++ )
			fin1 >> rom_M[ i ];

		cout << "[2] Loading NN weights..." << endl;
		fin2.open( "/home/ML310510221/Final_Project/SiameseNN/weights/weight.txt", ios::in );
		for ( int i = 0 ; i < ROM_WEIGHT_SIZE ; i++ )
			fin2 >> rom_M[ ROM_IMG_SIZE + i ];

		fin1.close();
		fin2.close();
		
		SC_METHOD( read_data );
		sensitive << clk.pos();
	}
};


