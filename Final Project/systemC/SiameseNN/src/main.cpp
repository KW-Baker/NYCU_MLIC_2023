/***************************************************************************************************/
// FILE NAME:    main.cpp
// VERSION:      1.0 
// DATE:         Jun 11, 2023
// AUTHOR:       KUAN-WEI, CHEN, NYCU IEE
// CODE TYPE:    CPP
// DESCRIPTION:  2023 Spring MLIC / Final Project
// MODIFICATION: 
// Date          Description
// 06/11       
/***************************************************************************************************/
#include "systemc.h"
#include "FSM.h"
#include "ROM.h"
#include "clockreset.h"
#include "Monitor.h"
#include <iostream>

using namespace std;

int sc_main( int argc,char* argv[] ) {
	// Ignore warning msg
    sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
                                           sc_core::SC_DO_NOTHING );

	sc_signal < bool > clk, rst;
	sc_fifo < bool > rom_rd;
	sc_fifo < sc_uint<31> > rom_addr;
	sc_fifo < float > data_in;
	sc_fifo < sc_int<19> > data_out;
	sc_fifo < bool > data_in_signal;
	sc_fifo < bool > data_out_signal;

	
	/* ---- Module instance here!!! ---- */
	Reset m_reset( "m_reset", 5 );
	Clock m_clock( "m_clock", 5, 500000 );
	FSM m_fsm( "m_fsm" );
	// Conv m_conv( "m_conv");
	ROM m_rom( "m_rom" );
	Monitor m_monitor( "m_monitor" );

	cout << "\n-------------------------\n";
	cout << "Starting Simulation..." << endl;

    /* ---- Pin assignment here!!! ---- */
	m_clock( clk );
	m_reset( rst );

	// FSM
	m_fsm.rst(rst);
	m_fsm.clk(clk);
	m_fsm.rom_rd(rom_rd);
	m_fsm.rom_addr(rom_addr);
	m_fsm.data_in(data_in);
	m_fsm.data_out(data_out);
	m_fsm.data_out_signal(data_out_signal);

	// ROM
	m_rom.clk(clk);
	m_rom.rom_rd(rom_rd);
	m_rom.rom_addr(rom_addr);
	m_rom.data(data_in);

	// Monitor
	m_monitor( rst, clk, data_out, data_out_signal );

	sc_start( );

	cout << "\n-------------------------\n";

	return 0;
}











