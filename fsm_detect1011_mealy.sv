module fsm_detect1011_mealy (
    input logic clk,
    input logic rst,
    input logic din,
    output logic dout
);

// in Mealy, the output updates when the input does and only stays high for the remainder of that clock cycle

typedef enum logic [1:0] {S0, S1, S10, S101} state_t;   // creates binary encoded state type; S0 is also INIT state
state_t state, next_state;

logic detected; // the intermediate output value that the flip-flop dout reads from

// block 1: state register
always_ff @(posedge clk) begin      // synchronous reset
    if (rst) state <= S0;
    else state <= next_state;
    dout <= detected;
end

// block 2: next state logic
always_comb begin
    case (state)
        S0: next_state = din ? S1 : S0;         // next state = S1 if input = 1, S0 if input = 0
        S1: next_state = din ? S1 : S10;        // next state = S1 if input = 1, S10 if input = 0
        S10: next_state = din ? S101 : S10;     // next state = S101 if input = 1, S0 if input = 0
        S101: next_state = din ? S1 : S10;      // next state = S1011 if input = 1, S0 if input = 0
        default: next_state = S0;
    endcase
end

// block 3: output logic, Mealy
always_comb begin
    case (state)
        S0: detected = 0;                       // S0, S1, S10 does not have any inputs that result in an output of 1
        S1: detected = 0;
        S10: detected = 0;
        S101: detected = din ? 1 : 0;           // when in S101, an input of 1 = 1011 -> output 1; else 0
        default: detected = 0;
    endcase
end

endmodule