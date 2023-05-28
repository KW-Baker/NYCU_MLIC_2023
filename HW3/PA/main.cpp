/***************************************************************************************************/
// FILE NAME:    main.cpp
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
#include "ROM.h"
#include "clockreset.h"
#include "Conv.h"
#include "Monitor.h"
#include <iostream>

using namespace std;

int sc_main( int argc,char* argv[] ) {
	// Ignore warning msg
    sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
                                           sc_core::SC_DO_NOTHING );

	sc_signal < bool > clk, rst;
	sc_signal < bool > rom_rd;
	sc_signal < sc_uint<7> > rom_addr;
	sc_signal < float > data_in;
	sc_signal < sc_int<19> > data_out;
	sc_signal < bool > data_in_signal;
	sc_signal < bool > data_out_signal;

	
	/* ---- Module instance here!!! ---- */
	Reset m_reset( "m_reset", 5 );
	Clock m_clock( "m_clock", 5, 200 );
	Conv m_conv( "m_conv");
	ROM m_rom( "m_rom" );
	Monitor m_monitor( "m_monitor" );

	cout << "\n-------------------------\n";

    /* ---- Pin assignment here!!! ---- */
	m_clock( clk );
	m_reset( rst );
	// m_rom( clk, rom_rd, rom_addr, data_in );
	m_rom.clk(clk);
	m_rom.rom_rd(rom_rd);
	m_rom.rom_addr(rom_addr);
	m_rom.data(data_in);

	// m_conv( rst, clk, rom_rd, rom_addr, data_in, data_out, data_out_signal );
	m_conv.rst(rst);
	m_conv.clk(clk);
	m_conv.rom_rd(rom_rd);
	m_conv.rom_addr(rom_addr);
	m_conv.data_in(data_in);
	m_conv.data_out(data_out);
	m_conv.data_out_signal(data_out_signal);
	m_monitor( rst, clk, data_out, data_out_signal );

	sc_start( );

	cout << "\n-------------------------\n";

	return 0;
}











