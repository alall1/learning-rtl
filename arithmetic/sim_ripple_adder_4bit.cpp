#include "Vripple_adder_4bit.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "top", which is essentially the handle to the hardware
    Vripple_adder_4bit* top = new Vripple_adder_4bit;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);   // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    top->trace(tfp, 99);            // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("ripple_adder_4bit.vcd"); // open output file to write signals to

    // === variables to use in loop ===
    vluint64_t sim_time = 0;    // verilator's name for a 64-bit unsigned integer; used as a simulation timestamp that ticks upward
    int errors = 0;         // a counter for how many test cases fail

    // === helper function ===
    auto testsum = [&](int A, int B, int& error_count) {
        // set inputs and eval
        top->A = A;
        top->B = B;
        top->eval();

        // incrementing time
        tfp->dump(sim_time++);

        // calculating reference
        int sum = A + B;
        int exp_S = sum & 0xF;
        int exp_Cout = (sum > 15) ? 1 : 0;

        // comparing & writing
        if (top->S != exp_S || top->Cout != exp_Cout) {
            printf("ERROR: A=%d B=%d; got S=%d Cout=%d; expected S=%d Cout=%d\n",
                    top->A, top->B, top->S, top->Cout, exp_S, exp_Cout);
            error_count++;
        } else {
            printf("OK: A=%d B=%d; got S=%d Cout=%d\n",
                    top->A, top->B, top->S, top->Cout);
        }
    };

    // === testing ===
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            testsum(i, j, errors);
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