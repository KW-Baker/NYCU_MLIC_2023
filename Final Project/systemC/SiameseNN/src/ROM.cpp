/***************************************************************************************************/
// FILE NAME:    ROM.cpp
// VERSION:      1.0 
// DATE:         MAY 01, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Final Project
// MODIFICATION: 
// Date          Description
// 06/11       
/***************************************************************************************************/
#include "ROM.h"


void ROM::read_data() {
	bool rd_en;
	sc_uint< 31 > addr;

	rom_rd->nb_read(rd_en);
	rom_addr->nb_read(addr);

	if ( rd_en )
		data->nb_write( rom_M[addr] );
}