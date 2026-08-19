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

**radix4_booth_mult**: a 5-bit multiplier that uses radix-4 Booth's algorithm to multiply two signed two's complement numbers and return a 10-bit signed product.
- uses the radix-4 version of Booth's algorithm to multiply two signed two's complement numbers.
- radix-4 Booth looks at a wider window; instead of comparing bit[i] and bit[i-1], it compares bit[i] with bit[i-1] AND bit[i+1]. 
- the radix-4 version of Booth's algorithm is used since there is no best or worst case; it will ALWAYS perform N / 2 operations, regardless of the bit values.
- one thing to note about radix-4 Booth is that it takes half the cycles of regular Booth; since the windows are wider, each "step" is separated by 2 arithmetic right shifts instead of 1. So, the number of cycles is equal to (N rounded up to nearest even number) / 2.

**fsm_detect1011_moore**: a Moore finite state machine (FSM) that detects input patterns of 1011 (single bit inputs)
- this FSM has 5 states: S0, S1, S10, S101, and S1011. S0 acts as the INIT/reset state, since a sequence doesn't "start" until a 1. This FSM is a Moore machine, meaning outputs ONLY depend on the current state. As such, the output of all the states is 0, except for S1011, which is the goal state.
- note that the output is only 1 on the clock cycle AFTER the pattern is seen: for 101100, the output would be 000010. This is because the current state is the only thing affecting the output, and it changes only on clock edges.
- one thing to note is that the pattern this FSM is looking for can overlap in input sequences; for example 1011011 is two overlapping patterns of 1011. To account for this, when a 0 is inputted and current state is S1011 OR S101, the next state will be S10 instead of S0, because both of these states are achieved when the previous input was a 1. If the next state was S0, the FSM would miss this pattern: 101011.

**fsm_detect1011_mealy**: a Mealy finite state machine (FSM) that detects input patterns of 1011 (single bit inputs)
- this FSM has 4 states, 1 less than the Moore implementation: S0, S1, S10, and S101. S0 again is the INIT/reset state. However, there is no S1011--since the outputs of Mealy machines can depend on current states AND inputs, an input of 1 to S101 can create that output of 1.
- note that the output is only 1 on the clock cycle AFTER the pattern is seen, like the Moore implementation. This is because I made the output a flip flop, updating to be an intermediate output value on the positive clock edge. I did this because the intermediate output value updates *whenever* the current state is S101 and the input is 1, regardless of whether the input stays 1 long enough to be captured by the positive clock edge and actually lead to a 1011 pattern. This would be fine if my testbench measured values at positive clock edges, but my testbench measures values in the middle of clock edges, while the input is still 1 long enough for the output to be measured but short enough to not be captured by the FSM.
- this FSM also handles overlap similarly to the Moore implementation, instead just at S101 since S1011 isn't a state anymore.
