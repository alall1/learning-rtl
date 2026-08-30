module fsm_stream_control (
    input logic clk,
    input logic rst,

    // Upstream interface
    input logic [7:0] in_data,
    input logic in_valid,
    output logic in_ready,

    // Downstream interface
    output logic [7:0] out_data,
    output logic out_valid,
    input logic out_ready
);

/* 
two states: empty & full

EMPTY:
    in_ready = 1
    out_valid = 0
    pop cannot be 1 while EMPTY
FULL:
    in_ready = 0 doesn't necessarily have to be the case; could push & pop at the same time in a later version
    out_valid = 1
    push cannot be 1 while FULL

*/

// push -> read new value, pop -> output current value
logic push, pop;
assign push = in_valid && in_ready;
assign pop = out_valid && out_ready;

logic state;    // 0 = empty, 1 = full
logic next_state;

// state register
always_ff @(posedge clk) begin
    if (rst) state <= 1'b0;
    else state <= next_state;
end

// next state logic
always_comb begin
    if (state == 1'b0) next_state = push;   // empty -> full state transition
    else next_state = ~pop;                 // full -> empty state transition
end

// output logic
always_comb begin
    if (state == 1'b0) begin    // if empty
        in_ready = 1'b1;
        out_valid = 1'b0;
    end else begin              // if full
        in_ready = 1'b0;
        out_valid = 1'b1;
    end
end

// output (out_data) logic
always_ff @(posedge clk) begin
    if (rst) out_data <= 8'b0000_0000;
    else if (state == 1'b0 && push) out_data <= in_data;
end

endmodule