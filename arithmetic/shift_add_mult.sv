module shift_add_mult (
    input logic clk,
    input logic rst,
    input logic [3:0] A,
    input logic [3:0] B,
    output logic [7:0] P
);

logic [1:0] cycle;      // can represent 0, 1, 2, 3; 3 is the max shift needed for 4-bit multiplication. Adjust for wider inputs
logic [7:0] sum;        // the sum calculated combinationally with P + shift_A, then stored back in P @ posedge clk
logic [6:0] shift_A;    // shift_A is given 7 bits, because at max it is shifted left by 3 (4 + 3 = 7)
logic [6:0] arg;        // the argument being added to the accumulated sum, either shift_A or all zeros based on the B[cycle]

always_comb begin
    shift_A = 7'(A) << cycle;     // A shifted left according to the current cycle
    arg = (B[cycle]) ? shift_A : 7'b0000000; 
    sum = P + arg;
end

always_ff @(posedge clk) begin
    if (rst) begin
        P <= 8'b00000000;
        cycle <= 2'b00;
    end else begin
        P <= sum;
        cycle <= cycle + 1'b1;
    end
end

endmodule