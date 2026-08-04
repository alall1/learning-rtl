module accumulator (
    input logic clk,
    input logic rst,
    input logic [3:0] A,
    output logic [5:0] S,
    output logic overflow
);

logic c0, c1, ovfl;
logic [5:0] sum;

ripple_adder_4bit ra (.A(A), .B(S[3:0]), .S(sum[3:0]), .Cout(c0));
carry_in_adder ca0 (.A(c0), .B(S[4]), .Cin(1'b0), .S(sum[4]), .Cout(c1));
carry_in_adder ca1 (.A(c1), .B(S[5]), .Cin(1'b0), .S(sum[5]), .Cout(ovfl));

always_ff @(posedge clk) begin
    // most designs with registers require a reset, to go back to a baseline and prevent Xs from propagating (FSMs, counters, accumulators like this one)
    if (rst) begin
        S <= 0;    // using nonblocking assignment <=
        overflow <= 0;
    end else begin
        S <= sum;
        if (overflow == 1) overflow <= 1;   // if overflow is 1, it should stay at 1 until reset, because sum never goes down
        else overflow <= ovfl;
    end
end

endmodule
