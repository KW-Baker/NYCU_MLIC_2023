#define ITERATION 10
#include "systemc.h"
#include <stdlib.h>

SC_MODULE(adder)
{
    sc_in_clk clk;
    sc_in < bool > rst;

    /* ---- Wire init here!!! ---- */
    sc_in < int > a, b;
    sc_out < int > c;
        
        

    /* ---- Wire init here!!! ---- */

    void Compute();

    SC_CTOR(adder)
    {
        SC_METHOD(Compute);
        sensitive << rst.pos() << clk.pos();
    }
};

SC_MODULE(pattern_gen)
{
    sc_in_clk clk;
    sc_in < bool > rst;
    sc_out< int > in1, in2;

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

        SC_METHOD(Generator);
        sensitive << rst.pos() << clk.pos();
    }
};

SC_MODULE(monitor)
{
	sc_in < bool > clk;
    sc_in < bool > rst;
    sc_in< int > eyes;

    int i = ITERATION+2;
    void Watch();

    SC_CTOR(monitor)
    {
        SC_METHOD(Watch);
        sensitive << rst.pos() << clk.pos();
    }
};
