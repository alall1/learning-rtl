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

**shift_add_mult**: a 4-bit multiplier that uses the shift-and-add algorithm to multiply two unsigned 4-bit numbers and return an 8-bit product.
- shift-and-add creates a partial product for every "1" in the multiplier; if there are *k* 1s, shift-and-add will do *k* operations.
- shift-and-add also takes *n* cycles for *n*-bit inputs.

**booth_mult**: a 4-bit multiplier that uses Booth's algorithm to multiply two SIGNED two's complement numbers and return an 8-bit SIGNED product.
- uses Booth's algorithm, which acts on the transitions between 0s and 1s in the multiplier instead of acting on every "1" like shift-and-add. This is advantageous when there are long series of consecutive 1s or 0s; each "train" of 1s only needs 2 add operations.
- however, in the worst case scenario (10101010...), Booth's algorithm actually does *double* the operations of regular shift-and-add, since it acts N times on N alternating bits but shift-and-add only acts N/2 times for each 1.
- this implementation of Booth's algorithm also takes *n* cycles for *n*-bit inputs, much like the shift-and-add implementation.
