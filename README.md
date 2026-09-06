# learning-rtl

### arithmetic
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

### fsms
**fsm_detect1011_moore**: a Moore finite state machine (FSM) that detects input patterns of 1011 (single bit inputs)
- this FSM has 5 states: S0, S1, S10, S101, and S1011. S0 acts as the INIT/reset state, since a sequence doesn't "start" until a 1. This FSM is a Moore machine, meaning outputs ONLY depend on the current state. As such, the output of all the states is 0, except for S1011, which is the goal state.
- note that the output is only 1 on the clock cycle AFTER the pattern is seen: for 101100, the output would be 000010. This is because the current state is the only thing affecting the output, and it changes only on clock edges.
- one thing to note is that the pattern this FSM is looking for can overlap in input sequences; for example 1011011 is two overlapping patterns of 1011. To account for this, when a 0 is inputted and current state is S1011 OR S101, the next state will be S10 instead of S0, because both of these states are achieved when the previous input was a 1. If the next state was S0, the FSM would miss this pattern: 101011.
- state diagram below:

	<img width="541" height="310" alt="fsm_state_1011moore" src="https://github.com/user-attachments/assets/b35cdf34-4d88-4ea6-b6c4-e7a7b5389ce4" />

**fsm_detect1011_mealy**: a Mealy finite state machine (FSM) that detects input patterns of 1011 (single bit inputs)
- this FSM has 4 states, 1 less than the Moore implementation: S0, S1, S10, and S101. S0 again is the INIT/reset state. However, there is no S1011--since the outputs of Mealy machines can depend on current states AND inputs, an input of 1 to S101 can create that output of 1.
- note that the output is only 1 on the clock cycle AFTER the pattern is seen, like the Moore implementation. This is because I made the output a flip flop, updating to be an intermediate output value on the positive clock edge. I did this because the intermediate output value updates *whenever* the current state is S101 and the input is 1, regardless of whether the input stays 1 long enough to be captured by the positive clock edge and actually lead to a 1011 pattern. This would be fine if my testbench measured values at positive clock edges, but my testbench measures values in the middle of clock edges, while the input is still 1 long enough for the output to be measured but short enough to not be captured by the FSM.
- this FSM also handles overlap similarly to the Moore implementation, instead just at S101 since S1011 isn't a state anymore.
- state diagram below:

	<img width="455" height="326" alt="fsm_state_1011mealy" src="https://github.com/user-attachments/assets/181c3fa9-e066-4cf0-a063-1a5e1ad5f8d6" />

**fsm_stream_control**: a simple valid/ready streaming controller, similar to flow-control interfaces used between blocks in pipelined RTL systems; uses a one-byte internal buffer to temporarily store data
- this FSM has 2 states: EMPTY and FULL. EMPTY is a state where the controller isn't holding valid data; this could be either before it receives any data or after it receives data and passes it downstream. FULL is a state where the controller is holding valid data that hasn't been passed downstream again.
- the valid/ready handshake guarantees that data is only accepted or transmitted when the corresponding valid/ready handshake succeeds (in or out), preventing duplication or overwriting.
- push (upstream valid/ready handshake succeeds) decides if EMPTY -> FULL, and pop (downstream valid/ready handshake succeeds) decides if FULL -> EMPTY.
- this version is a Moore FSM, since the FSM outputs depend only on the current state, not directly on the inputs.
- state diagram below:

	<img width="460" height="181" alt="fsm_stream_control" src="https://github.com/user-attachments/assets/eee76417-5464-42d4-8e1b-487c9f363126" />

- a Yosys/Graphviz visualization of fsm_stream_control:

	<img width="500" height="529" alt="vis_fsm_stream_control" src="https://github.com/user-attachments/assets/5b821315-3a7f-42b6-a0cc-cc71c2126b9b" />

### blocks
**sync_fifo**: a parameterizable synchronous first-in, first-out (FIFO) buffer which has variable depth and data width; used to 'decouple' consumer from producer by "absorbing" the slack of a slow consumer (appending produced data into a queue) without stalling the producer or dropping data
- made up of 1. a block of memory, where elements are stored, 2. a write pointer, the index of the next slot to write into, and 3. a read pointer, the index of the next slot to read from. On a write, the write data is stored at mem[wr_ptr], and wr_ptr is incremented by 1. On a read, the data stored at mem[rd_ptr] is read and rd_ptr is incremented. Both pointers wrap around to zero when they "run off" the end. Writes and reads can happen on the same clock edge; however, when the buffer is empty, reading and writing simultaneously will write a value, but not read it, and when the buffer is full, reading and writing simultaneously will only read the value, not write the new one.
- to differentiate between a full state and empty state, a wrap bit was added to both pointers; an extra bit that flips each time a pointer wraps around to zero. The buffer is full when the address bits of the pointers are equal, but the wrap bits of the pointers are different (wr_ptr is essentially a full lap ahead of rd_ptr), and writes can no longer happen; and empty when all bits of the pointers are equal (wr_ptr == rd_ptr), and reads can no longer happen.
- full and empty flags are also exposed as outputs, because producers writing into the buffer must know when to stall instead of trying to write data to a full buffer, and consumers reading from the buffer must know when to stall instead of reading and computing on non-existent values. "almost-full" and "almost-empty" flags are exposed in many other designs, because producers/consumers may need a few cycles of warning before they stall; however, this design doesn't have them.

**fixed_arbiter**: a parameterizable fixed-priority arbiter that takes in requests in the form of a request_bus, ordered from highest priority to lowest priority MSB to LSB; asserts a single grant to the highest priority requester for multiple cycles until the granted master finishes and asserts ack, then rearbitrates; surfaces signal "locked" while asserting a grant for however many cycles the granted master needs
- number of requesters *N* is parameterizable, changes the size of request_bus and grant_bus. Signal grant_next is driven by combinational logic, and output grant_bus is a register, driven by sequential logic deciding whether to re-arbitrate this cycle, or continue asserting grant.
- signal "locked" is asserted by the arbiter while asserting a grant to a requester; only when signal "ack" is asserted by the granted master does locked de-assert. However, if there are non-zero requesters AND "ack" is asserted on the same cycle, locked stays asserted, but the arbiter re-arbitrates and the granted requester updates.
- with a fixed-priority arbiter, starvation is a real issue; if the top-priority requester requests every cycle, the rest of the requesters will never be served. This locks out every other requester, which may be okay when the fixed priorities genuinely reflect importance, but bad when requesters are of similar priority.

**round_robin_arbiter**: a parameterizable round-robin arbiter that takes in requests in the form of a request_bus, each bit corresponding to a requester, and asserts a single grant to the highest priority requester (during that cycle) for multiple cycles until the granted master finishes and asserts ack; surfaces "locked" while asserting a grant
- number of requesters is parameterizable, and changes the size of request_bus and grant_bus. Output is a register that is driven by sequential logic deciding whether to re-arbitrate this cycle or continue asserting grant.
- to avoid the starvation problem of fixed-priority arbiters, this design has a round-robin priority scheme. After a reset, the MSB is the highest priority requester, descending to the lowest priority requester at the LSB. However, when a certain requester is granted, the priority order is circled around (still in order), now starting at the requester exactly 1 bit AFTER the requester that was granted last cycle. So, the requester that was previously granted falls to the lowest priority.
	- example: 
		- priority order pre-clock-edge: 3, 2, 1, 0; requester 2 is granted
		- priority order post-clock-edge: 1, 0, 3, 2
	- another example:
		- priority order pre-clock-edge: 3, 2, 1, 0; requester 0 is granted
		- priority order post-clock-edge: 3, 2, 1, 0
	- note how if the lowest-priority requester is granted on a cycle, the order stays the same, because it continues to be the lowest-priority requester
- this avoids starvation because in the worst case a requester waits `N - 1` cycles before its turn comes up. Every requester, at some point, becomes highest priority. The cost of this round-robin arbiter is simply more logic. 
