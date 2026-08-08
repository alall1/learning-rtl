#include "Vshift_add_mult.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()

uint seed = 1234512;       // seed for Xorshift random number generator

int rand_num_16();

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "top", which is essentially the handle to the hardware
    Vshift_add_mult* top = new Vshift_add_mult;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);   // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    top->trace(tfp, 99);            // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("shift_add_mult.vcd"); // open output file to write signals to

    // === variables to use in loop ===
    vluint64_t sim_time = 0;    // verilator's name for a 64-bit unsigned integer; used as a simulation timestamp that ticks upward
    int errors = 0;         // a counter for how many test cases fail

    // === helper functions ===
    auto tick = [&]() {    // tick one clock cycle, one clk cycle = 2 waveform time units
        top->clk = 0;           // setting clk to 0
        top->eval();            // evaluating outputs during first half of clk cycle
        tfp->dump(sim_time++);  // reading current values & incrementing time

        top->clk = 1;           // setting clk to 1
        top->eval();            // evaluating outputs during second half of clk cycle
        tfp->dump(sim_time++);  // reading current vals & incrementing time
    };

    auto testmult = [&](int A, int B) {
        // set inputs and eval
        top->A = A;
        top->B = B;

        // calculating reference
        uint exp_P = A * B;

        // ticking 4 times, N-bit multiplication using shift-and-add takes N cycles
        tick();
        tick();
        tick();
        tick();
        
        // comparing & writing
        if (top->P != exp_P) {
            printf("ERROR: A=%d B=%d; got P=%d ; expected P=%d\n",
                    A, B, top->P, exp_P);
            errors++;
        } else {
            printf("OK: A=%d B=%d; got P=%d\n",
                    A, B, top->P);
        }
    };

    // === testing ===

    // set rst high for 1 tick to reset shift_add_mult
    top->rst = 1;
    tick();
    top->rst = 0;

    // testing the module with random 4-bit numbers
    testmult(rand_num_16(), rand_num_16());


    // set rst high for 1 tick to reset shift_add_mult (just to fully test reset working this time)
    top->rst = 1;
    tick();
    top->rst = 0;

    // testing the module with random 4-bit numbers after reset
    testmult(rand_num_16(), rand_num_16());

    // set rst high for 1 tick to reset shift_add_mult (just to fully test reset working this time)
    top->rst = 1;
    tick();
    top->rst = 0;

    // testing the module with random 4-bit numbers after reset
    testmult(rand_num_16(), rand_num_16());

    tfp->dump(sim_time++); // taking an extra sample so the last case has visible width

    // === cleanup ===
    tfp->close();   // close the waveform file so it is written to disk
    delete top;     // free the memory allocated with "new"

    // === final report ===
    if (errors == 0) printf("\nAll test cases passed.\n");
    else printf("\n%d test case(s) failed.\n", errors);

    return errors ? 1 : 0; // return 0 if no errors, or 1 if there were.
}

// random number generator helper (uses xorshift to generate a number between 0 and 15)
int rand_num_16 () {
    uint x = seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    seed = x & 4294967295;
    return x & 0xF;
}