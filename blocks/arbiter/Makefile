# cocotb Makefile for "sync_fifo" module
#
#   make                 # run
#   make WAVES=1         # run + dump waves for GTKWave
#   make clean
 
SIM ?= verilator
TOPLEVEL_LANG ?= verilog

VERILOG_SOURCES += sync_fifo.sv

TOPLEVEL = sync_fifo
COCOTB_TEST_MODULES = test_sync_fifo

COMPILE_ARGS += -GDEPTH=13 -GDATA_WIDTH=8
EXTRA_ARGS   += --trace --trace-structs
 
ifeq ($(WAVES),1)
    export COCOTB_TRACE = 1
endif
 
include $(shell cocotb-config --makefiles)/Makefile.sim
 
clean::
	rm -rf sim_build __pycache__ results.xml dump.fst dump.vcd