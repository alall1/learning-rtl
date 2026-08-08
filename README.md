# learning-rtl

**carry_in_adder**: a basic 1-bit adder that takes in two 1-bit adders plus a carry-in and returns the sum and a carry-out.


**ripple_adder_4bit**: a ripple-carry 4-bit adder that does not take in a carry-in but returns a sum and carry-out.
- used *carry_in_adder* for this module

**accumulator**: a 6-bit accumulator that adds 4-bit numbers to a running total sum and returns an overflow if the sum is larger than the range (unsigned binary, max number = 63)
- used a combination of *carry_in_adder* and *ripple_adder_4bit* for this module
- used `always_ff` to create flip-flops to store the running sum
	- one error I encountered here was the propagation of the `X` value through this module; Verilator automatically zeroes `X` values, so this was hard to catch. Fixed by implementing reset behavior.
	- I also created a `tick();` function in the testbench to simulate going through one clock cycle, so that my testbench code was cleaner

**param_adder**: a variable-bit two's complement adder that adds two numbers of a given bit width and saturates on overflow
- compared the input sign bits and output sign bit to detect overflow--overflow happens when two numbers of the same sign create a sum that has the opposite sign
	- detecting this sign bit (0 or 1) tells you if the overflow is positive or negative, which the module then saturates to either the positive limit or the negative limit of the bit width [2^(n-1) - 1, 2^(n-1)]
- only works up to 31 bits, as the simulator breaks at 32 bits (uses regular ints to represent the numbers). Future fix is to use int64_t/uint64_t to store larger numbers, and module should work at that range as well

