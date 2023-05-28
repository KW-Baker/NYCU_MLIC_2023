/***************************************************************************************************/
// FILE NAME:    ROM.cpp
// VERSION:      1.0 
// DATE:         MAY 01, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Homework3 / CNN (PA)
// MODIFICATION: 
// Date          Description
// 05/28        
/***************************************************************************************************/
#include "ROM.h"


void ROM::read_data() {
	bool rd_en;
	sc_uint< 7 > addr;

	rd_en = rom_rd.read();
	addr = rom_addr.read();

	if ( rd_en )
		data.write( rom_M[addr] );

}