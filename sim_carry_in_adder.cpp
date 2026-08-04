#include "Vcarry_in_adder.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "top", which is essentially the handle to the hardware
    Vcarry_in_adder* top = new Vcarry_in_adder;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);   // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    top->trace(tfp, 99);            // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("carry_in_adder.vcd"); // open output file to write signals to

    // === variables to use in loop ===
    vluint64_t time = 0;    // verilator's name for a 64-bit unsigned integer; used as a simulation timestamp that ticks upward
    int errors = 0;         // a counter for how many test cases fail

    // === test loop ===
    for (int i = 0; i < 8; i++) {
        // for this specific testbench, use the 3 bits of the number i to generate every input combination, like a truth table. top->variable is how to call variables from the "top" module; inputs or outputs
        top->A   = (i >> 0) & 1;    // bit 0 (LSB) of i -> port A
        top->B   = (i >> 1) & 1;    // bit 1 of i -> port B
        top->Cin = (i >> 2) & 1;    // bit 2 of i -> port Cin
        
        // evaluate the design: propagate the inputs through the logic so the outputs update. Required after changing inputs, otherwise checks will have the output's old values
        top->eval();

        // record all signals to the waveform at the current time, then increment time by 1
        tfp->dump(time++);

        // === computing the reference outputs independently in C++ ===
        int sum = top->A + top->B + top->Cin;   // adding inputs together (NOTE: this becomes an integer (0, 1, 2, or 3))
        int exp_S = sum & 1; // expected S value is the lowest bit of sum
        int exp_Cout = (sum >> 1) & 1; // expected Cout is the second-to-last bit of sum

        // === comparing reference outputs to hardware's outputs ===
        if (top->S != exp_S || top->Cout != exp_Cout) {
            // print error message
            printf("ERROR: A=%d B=%d Cin=%d; got S=%d Cout=%d; expected S=%d Cout=%d\n",
                top->A, top->B, top->Cin, top->S, top->Cout, exp_S, exp_Cout);

            errors++;   // add 1 to errors
        } else {
            printf("OK: A=%d B=%d Cin=%d; S=%d Cout=%d\n",
                top->A, top->B, top->Cin, top->S, top->Cout);
        }
    }

    tfp->dump(time++); // taking an extra sample so the last case has visible width

    // === cleanup ===
    tfp->close();   // close the waveform file so it is written to disk
    delete top;     // free the memory allocated with "new"

    // === final report ===
    if (errors == 0) printf("\nAll 8 test cases passed.\n");
    else printf("\n%d test case(s) failed.\n", errors);

    return errors ? 1 : 0; // return 0 if no errors, or 1 if there were.
}