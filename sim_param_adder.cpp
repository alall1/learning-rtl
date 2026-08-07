#include "Vparam_adder.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "top", which is essentially the handle to the hardware
    Vparam_adder* top = new Vparam_adder;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);   // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    top->trace(tfp, 99);            // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("param_adder.vcd"); // open output file to write signals to

    // === variables to use in loop ===
    vluint64_t sim_time = 0;    // verilator's name for a 64-bit unsigned integer; used as a simulation timestamp that ticks upward
    int errors = 0;             // a counter for how many test cases fail

    // === helper function ===
    auto testsum = [&](int A, int B, int width) {
        // set inputs and eval
        top->A = A;
        top->B = B;
        top->eval();

        // incrementing time
        tfp->dump(sim_time++);

        // calculating reference
        int sum = A + B;
        int exp_ovfl;

        unsigned int mask = (1 << width) - 1;   // creating a mask of 1s to match width variable
        unsigned int exp_S = sum & mask;        // bitwise AND between the calculated sum and the mask to get the EXACT expected S output bits; however, C++'s int is unsigned

        int max_pos = (1 << (width-1)) - 1;
        int max_neg = -(1 << (width-1));
        
        if (sum > max_pos) {            // overflowing positively
            exp_ovfl = 1;
        } else if (sum < max_neg) {     // overflowing negatively
            exp_ovfl = 1;
        } else {                        // no overflow
            exp_ovfl = 0;
        }

        // comparing & writing
        if (top->S != exp_S || top->ovfl != exp_ovfl) {
            printf("ERROR: A=%d B=%d; got S=%x ovfl=%d; expected S=%b ovfl=%d\n",
                    A, B, top->S, top->ovfl, exp_S, exp_ovfl);
            errors++;
        } else {
            printf("OK: A=%d B=%d; got S=%x ovfl=%d\n",
                    A, B, top->S, top->ovfl);
        }
    };

    // === testing ===
    testsum(15, 10, 6);     // no overflow, positive
    testsum(-23, -5, 6);    // no overflow, negative
    testsum(15, 17, 6);     // positive overflow
    testsum(-15, -18, 6);     // negative overflow

    tfp->dump(sim_time++); // taking an extra sample so the last case has visible width

    // === cleanup ===
    tfp->close();   // close the waveform file so it is written to disk
    delete top;     // free the memory allocated with "new"

    // === final report ===
    if (errors == 0) printf("\nAll test cases passed.\n");
    else printf("\n%d test case(s) failed.\n", errors);

    return errors ? 1 : 0; // return 0 if no errors, or 1 if there were.
}