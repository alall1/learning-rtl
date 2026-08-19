module fsm_detect1011_moore (
    input logic clk,
    input logic rst,
    input logic din,
    output logic dout
);

typedef enum logic [2:0] {S0, S1, S10, S101, S1011} state_t;   // creates binary encoded state type; S0 is also INIT state
state_t state, next_state;

// block 1: state register
always_ff @(posedge clk) begin      // synchronous reset
    if (rst) state <= S0;
    else state <= next_state;
end

// block 2: next state logic
always_comb begin
    case (state)
        S0: next_state = din ? S1 : S0;         // next state = S1 if input = 1, S0 if input = 0
        S1: next_state = din ? S1 : S10;        // next state = S1 if input = 1, S10 if input = 0
        S10: next_state = din ? S101 : S0;      // next state = S101 if input = 1, S0 if input = 0
        S101: next_state = din ? S1011 : S0;    // next state = S1011 if input = 1, S0 if input = 0
        S1011: next_state = din ? S1 : S10;     // next state = S1 if input = 1, S10 if input = 0 because overlapping sequences of 1011 counnt (e.g. 1011011 = 00001001)
        default: next_state = S0;
    endcase
end

// block 3: output logic, Moore
always_comb begin
    case (state)
        S0: dout = 0;
        S1: dout = 0;
        S10: dout = 0;
        S101: dout = 0;
        S1011: dout = 1;
        default: dout = 0;
    endcase
end

endmodule