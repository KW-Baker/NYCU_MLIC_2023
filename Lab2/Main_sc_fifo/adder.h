#define ITERATION 10
#include "systemc.h"
#include <stdlib.h>

SC_MODULE(adder)
{
    sc_in_clk clk;
    sc_in < bool > rst;

    /* ---- Channel init here!!! ---- */
    sc_port< sc_fifo_in_if< int > > a;
    sc_port< sc_fifo_in_if< int > > b;
    sc_port< sc_fifo_out_if< int > > c;
    
    
    void Compute();

    SC_CTOR(adder)
    {
        SC_THREAD(Compute);
        sensitive << rst.pos() << clk.pos();
    }
};

SC_MODULE(pattern_gen)
{
    sc_in_clk clk;
    sc_in < bool > rst;

    /* ---- Channel init here!!! ---- */
    sc_port< sc_fifo_out_if< int > > in1, in2;


    int data[ ITERATION*2 ] = {0}, addr = 0;
    void Generator();

    SC_CTOR(pattern_gen)
    {
        for(int i = 0; i < ITERATION*2; i+=2)
        {
            srand( i+1 );
            data[ i ] = rand() % 100;
            data[ i+1 ] = rand() % 100;
        }

        SC_THREAD(Generator);
        sensitive << rst.pos() << clk.pos();
    }
};

SC_MODULE(monitor)
{
	sc_in < bool > clk;
    sc_in < bool > rst;

    /* ----  Channel init here!!! ---- */
    sc_port< sc_fifo_in_if< int > > eyes;
    

    int i = ITERATION;
    void Watch();

    SC_CTOR(monitor)
    {
        SC_THREAD(Watch);
        sensitive << rst.pos() << clk.pos();
    }
};
