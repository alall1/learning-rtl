#include "Vfsm_detect1011_moore.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()
#include <vector>               // for sequence vector + last4 vector

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "top", which is essentially the handle to the hardware
    Vfsm_detect1011_moore* top = new Vfsm_detect1011_moore;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);   // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    top->trace(tfp, 99);            // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("fsm_detect1011_moore.vcd"); // open output file to write signals to

    // === variables to use in loop ===
    vluint64_t sim_time = 0;    // verilator's name for a 64-bit unsigned integer; used as a simulation timestamp that ticks upward
    int errors = 0;         // a counter for how many test cases fail
    std::vector<int> sequence = {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0};    // sequence to test on, needs 1 extra X at the end to see the output of the second-to-last item
    std::vector<int> last4;     // last 4 seen digits in the sequence

    auto tick = [&]() {    // tick one clock cycle, one clk cycle = 2 waveform time units
        top->clk = 0;           // setting clk to 0
        top->eval();            // evaluating outputs during first half of clk cycle
        tfp->dump(sim_time++);  // reading current values & incrementing time

        top->clk = 1;           // setting clk to 1
        top->eval();            // evaluating outputs during second half of clk cycle
        tfp->dump(sim_time++);  // reading current vals & incrementing time
    };

    // === test loop ===
    top->rst = 1;
    tick();
    top->rst = 0;

    for (int num : sequence) {
        top->din = num;

        /* debugging
        for (int n : last4) {
            printf("%d ", n);
        }
        printf("\n");
        */

        int exp_dout = (last4 == std::vector<int>{1, 0, 1, 1});     // computing exp_dout BEFORE appending new din (happens within current clock cycle)

        last4.push_back(num);       // adding new number as last item in vector
        if (last4.size() > 4) {
            last4.erase(last4.begin()); // erase the first item if vector is full, to keep it at a constant 4 last seen
        }

        if (top->dout != exp_dout) {
            errors++;
            printf("ERROR: din=%d; got dout=%d; expected dout=%d\n",
                    num, top->dout, exp_dout);
        } else {
            printf("OK: din=%d; got dout=%d; expected dout=%d\n",
                    num, top->dout, exp_dout);
        }

        tick(); // tick at the end of each loop
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