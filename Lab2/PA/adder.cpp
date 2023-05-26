#include "adder.h"

void adder::Compute()
{
    if ( rst ){}
    else
    {
        /* ---- Write adder function here!!! ---- */
        // cout << "a= " << a.read() << ", b= " << b.read() << endl;
        c.write( a.read() + b.read() );
        /* ---- Write adder function here!!! ---- */
    }
}

void pattern_gen::Generator()
{
    if ( rst ){}
    else
    {
        in1.write( data[ addr ] );
        in2.write( data[ addr+1 ] );
        addr += 2;     
    }
}

void monitor::Watch()
{
    if ( rst ){}
    else
    {
        if ( eyes.read() ) cout << "Computation result = " << eyes.read() << endl;
        i--;
        if (i == 0) sc_stop();    
    }
}