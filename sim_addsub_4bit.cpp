#include "Vaddsub_4bit.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "top", which is essentially the handle to the hardware
    Vaddsub_4bit* top = new Vaddsub_4bit;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);   // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    top->trace(tfp, 99);            // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("addsub_4bit.vcd"); // open output file to write signals to

    // === variables to use in loop ===
    vluint64_t sim_time = 0;    // verilator's name for a 64-bit unsigned integer; used as a simulation timestamp that ticks upward
    int errors = 0;         // a counter for how many test cases fail

    // === helper function ===
    auto testsum = [&](int A, int B) {
        // set inputs and eval
        top->A = A;
        top->B = B;
        top->eval();

        // incrementing time
        tfp->dump(sim_time++);

        // calculating reference
        int sum = A + B;

        int exp_S;
        int exp_ovfl;

        // checking if sum is out of bounds (overflow), which then updates exp_S to be the max positive/negative value because hardware uses saturation to handle overflow
        if (sum > 7) {
            exp_S = 7;
            exp_ovfl = 1;
        } else if (sum < -8) {
            exp_S = -8;
            exp_ovfl = 1;
        } else {
            exp_S = sum;
            exp_ovfl = 0;
        }

        // comparing & writing
        if (top->S != exp_S || top->ovfl != exp_ovfl) {
            printf("ERROR: A=%d B=%d; got S=%d ovfl=%d; expected S=%d ovfl=%d\n",
                    top->A, top->B, top->S, top->ovfl, exp_S, exp_ovfl);
            errors++;
        } else {
            printf("OK: A=%d B=%d; got S=%d ovfl=%d\n",
                    top->A, top->B, top->S, top->ovfl);
        }
    };

    // === testing ===
    for (int i = -8; i < 8; i++) {
        for (int j = -8; j < 8; j++) {
            testsum(i, j);
        }
    }

    tfp->dump(sim_time++); // taking an extra sample so the last case has visible width

    // === cleanup ===
    tfp->close();   // close the waveform file so it is written to disk
    delete top;     // free the memory allocated with "new"

    // === final report ===
    if (errors == 0) printf("\nAll test cases passed.\n");
    else printf("\n%d test case(s) failed.\n", errors);

    return errors ? 1 : 0; // return 0 if no errors, or 1 if there were.
}