/***************************************************************************************************/
// FILE NAME:    Monitor.cpp
// VERSION:      1.0 
// DATE:         MAY 01, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Homework3 / CNN
// MODIFICATION: 
// Date          Description
// 05/28        
/***************************************************************************************************/
#include "Monitor.h"


void Monitor:: monitor() {
	
	bool in_valid;
	sc_int< 19 > data;

	data_in_signal->nb_read( in_valid );
	data_in->nb_read(data);

	if ( rst ) {
		x = 0;
		y = 0;
		cout << "Result: " << endl;
		return;
	}
	else if ( in_valid ) {
		cout << data << "\t";
		
		x = x + 1;
		if ( x == 8 ) {
			x = 0;
			y = y + 1;
			cout << endl;
			if ( y == 8 ) {
				sc_stop();
			}
		}		
	}
}


