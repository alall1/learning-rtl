#include "Vbooth_mult.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()
#include <cstdint>              // standard C++ library for int8_t and uint32_t

uint seed = 1234512;       // seed for Xorshift random number generator

int rand_sign_4bit();

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "top", which is essentially the handle to the hardware
    Vbooth_mult* top = new Vbooth_mult;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);   // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    top->trace(tfp, 99);            // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("booth_mult.vcd"); // open output file to write signals to

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
        // set inputs
        top->M = A;
        top->Q = B;

        // reset (to clean up testing code, and so "r" picks up the real Q instead of the pre-reset Q)
        top->rst = 1;
        tick();
        top->rst = 0;

        // calculating reference
        int real_P = A * B;
        int exp_P = real_P & 0xFF;  // & 0xF because module will return as raw 8 bits

        // ticking 4 times, N-bit multiplication using shift-and-add takes N cycles
        tick();
        tick();
        tick();
        tick();
        
        // comparing & writing
        if (top->P != exp_P) {
            printf("ERROR: A=%d B=%d; got P=%d ; expected P=%d real P=%d\n",
                    A, B, top->P, exp_P, real_P);
            errors++;
        } else {
            printf("OK: A=%d B=%d; got P=%d\n",
                    A, B, top->P);
        }
    };

    // === testing ===

    for (int i = -8; i < 8; i++) {
        for (int j = -8; j < 8; j++) {
            testmult(i, j);
        }
    }
    /*
    testmult(rand_sign_4bit(), rand_sign_4bit());
    testmult(rand_sign_4bit(), rand_sign_4bit());
    tick();     // testing if "count" works, doesn't do any ops after mult finishes
    testmult(rand_sign_4bit(), rand_sign_4bit());
    testmult(rand_sign_4bit(), rand_sign_4bit());
    testmult(rand_sign_4bit(), rand_sign_4bit());
    */

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
int rand_sign_4bit () {
    uint32_t x = seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    seed = x;
    int8_t v = x & 0xF;             // low 4 bits, 0..15
    if (v & 0x8) v |= 0xF0;         // if bit 3 (sign bit of 4-bit twos complement) = 1 → fill upper bits with 1s
    return v;
}