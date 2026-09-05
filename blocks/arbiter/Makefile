# cocotb Makefile for "fixed_arbiter" module
#
#   make                 # run
#   make WAVES=1         # run + dump waves for GTKWave
#   make clean
 
SIM ?= verilator
TOPLEVEL_LANG ?= verilog

VERILOG_SOURCES += fixed_arbiter.sv

TOPLEVEL = fixed_arbiter
COCOTB_TEST_MODULES = test_fixed_arbiter

N ?= 4

COMPILE_ARGS += -GN=$(N)
 
ifeq ($(WAVES), 1)
	EXTRA_ARGS   += --trace --trace-structs
    export COCOTB_TRACE = 1
endif
 
include $(shell cocotb-config --makefiles)/Makefile.sim
 
clean::
	rm -rf sim_build __pycache__ results.xml dump.fst dump.vcd