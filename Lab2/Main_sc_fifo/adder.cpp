#include "adder.h"

void adder::Compute()
{
    if ( rst ){}
    else
    {
        /* ---- Write adder function here!!! ---- */
        while(true){
            c->write( a->read() + b->read() );
        }
    }
}

void pattern_gen::Generator()
{
    if ( rst ){}
    else
    {
        while(addr <= ITERATION*2)
        {
            in1->write( data[ addr ] );
            in2->write( data[ addr+1 ] );
            addr += 2;             
        }
    }
}

void monitor::Watch()
{
    if ( rst ){}
    else
    {
        while(i--)
            cout << "Computation result = " << eyes->read() << endl;             
        sc_stop();
    }
}