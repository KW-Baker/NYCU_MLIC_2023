#include "adder.h"
#include "clockreset.h"

/* Description: random generator for adder computing with different channels usage */

int sc_main(int agrc, char *argv[])
{
    // Ignore warning msg
    sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
                                           sc_core::SC_DO_NOTHING );
    // Clock, Reset signal init
    sc_signal < bool > clk, rst;
    
    /* ---- Channel init here!!! ---- */
    sc_fifo < int > a(10), b(10), c(10);


    /* ---- Module instance here!!! ---- */
    Clock m_clock("m_clock", 5, 20);
    Reset m_rst("m_rst", 4);
    adder m_adder("m_adder");
    pattern_gen m_gen("m_gen");
    monitor m_eyes("m_eyes");


    cout << "\n-------------------------\n";

    /* ---- Pin assignment here!!! ---- */
    m_clock(clk);
    m_rst(rst);
    m_gen(clk, rst, a, b);
    m_adder(clk, rst, a, b, c);
    m_eyes(clk, rst, c);

    sc_start( );

    cout << "-------------------------\n";
    return 0;
}