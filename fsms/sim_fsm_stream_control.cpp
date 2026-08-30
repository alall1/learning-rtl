#include "Vfsm_stream_control.h"    // the C++ class Verilator generated from Verilog; "V" + module name because Verilator prefixes generated class with V (for "Verilated")
#include "verilated.h"          // core Verilator runtime functions
#include "verilated_vcd_c.h"    // VCD tracing support, for writing waveform files for GTKWave
#include <cstdio>               // standard C++ library for printf()
#include <vector>               // for vector arrays

int main(int argc, char** argv) {
    // handing command-line args to Verilator so flags work
    Verilated::commandArgs(argc, argv);

    // creating new instance of design; "new" allocates it and returns a pointer "dut", which is essentially the handle to the hardware
    Vfsm_stream_control* dut = new Vfsm_stream_control;

    // === tracing setup for waveform file ===
    Verilated::traceEverOn(true);           // globally enable waveform tracing
    VerilatedVcdC* tfp = new VerilatedVcdC; // create the trace object (the thing that writes the file)
    dut->trace(tfp, 99);                    // connect the trace to the design; 99 = how deep into the module hierarchy to record (recording submodule waveforms)
    
    tfp->open("fsm_stream_control.vcd");    // open output file to write signals to

    // === variables to use in loop ===
    vluint64_t sim_time = 0;    // verilator's name for a 64-bit unsigned integer; used as a simulation timestamp that ticks upward
    int errors = 0;             // a counter for how many test cases fail
    
    std::vector<int> in_valid  = {0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0};    // in_valid waveform (changes on negedge clk, halfway through clock cycles)
    std::vector<int> out_ready = {0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1};    // out_ready waveform
    std::vector<int> in_data   = {14, 2, 253, 47};
    int data_ind = 0;           // index of in_data, incremented only when in_valid & in_ready are both 1 on a clock cycle
    int state = 0;              // current state for simulator, 0 = EMPTY, 1 = FULL
    int exp_out_data = 0;
    int count = 0;

    // === helper functions ===
    auto tick = [&]() {    // tick one clock cycle, one clk cycle = 2 waveform time units
        dut->clk = 0;           // setting clk to 0
        dut->eval();            // evaluating outputs during first half of clk cycle
        tfp->dump(sim_time++);  // reading current values & incrementing time

        dut->clk = 1;           // setting clk to 1
        dut->eval();            // evaluating outputs during second half of clk cycle
        tfp->dump(sim_time++);  // reading current vals & incrementing time
    };

    // === testing ===
    dut->rst = 1;
    tick();
    dut->rst = 0;
    tick();

    for (int i = 0; i < in_valid.size(); i++) {
        dut->in_valid  = in_valid[i];
        dut->out_ready = out_ready[i];

        // keep presenting the current data item until DUT accepts it
        if (data_ind < in_data.size()) dut->in_data = in_data[data_ind];
        else dut->in_data = 0;


        // determining what should happen at posedge clk
        int next_state = state;
        int next_out_data = exp_out_data;

        if (state == 0) {  // EMPTY
            // in_ready should be 1 in EMPTY, so in_valid=1 means an input handshake occurs
            if (in_valid[i]) {
                if (data_ind >= in_data.size()) {
                    printf("ERROR cycle %d: testbench ran out of input data\n", i);
                    errors++;
                } else {
                    next_out_data = in_data[data_ind];
                    data_ind++;
                    next_state = 1;  // FULL
                }
            }
        } else {  // FULL
            // out_valid should be 1 in FULL, so out_ready=1 means an output handshake occurs
            if (out_ready[i]) {
                next_state = 0;  // EMPTY
            }
        }

        // posedge clk
        tick();

        // update reference
        state = next_state;
        exp_out_data = next_out_data;

        // checking DUT outputs after posedge
        int exp_in_ready = (state == 0);
        int exp_out_valid = (state == 1);

        if (dut->in_ready != exp_in_ready) {
            printf(
                "ERROR cycle %d: in_ready = %d, expected %d\n",
                i, dut->in_ready, exp_in_ready
            );
            errors++;
        }

        if (dut->out_valid != exp_out_valid) {
            printf(
                "ERROR cycle %d: out_valid = %d, expected %d\n",
                i, dut->out_valid, exp_out_valid
            );
            errors++;
        }

        // out_data only matters when out_valid = 1
        if (exp_out_valid && dut->out_data != exp_out_data) {
            printf(
                "ERROR cycle %d: out_data = %d, expected %d\n",
                i,
                dut->out_data,
                exp_out_data
            );
            errors++;
        }
        count++;
    }

    tfp->dump(sim_time++); // taking an extra sample so the last case has visible width

    // === cleanup ===
    tfp->close();   // close the waveform file so it is written to disk
    delete dut;     // free the memory allocated with "new"

    // === final report ===
    if (errors == 0) printf("\nAll %d test cases passed.\n", count);
    else printf("\n%d test case(s) failed.\n", errors);

    return errors ? 1 : 0; // return 0 if no errors, or 1 if there were.
}