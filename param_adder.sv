module addsub_4bit (
    input logic [3:0] A,
    input logic [3:0] B,
    input logic sub,
    output logic [3:0] S,
    output logic ovfl
);

logic Cout;
logic [3:0] sum;
logic [3:0] inp_b;

ripple_adder_4bit ra (.A(A), .B(inp_b), .S(sum), .Cout(Cout));

always_comb begin
    if (sub) inp_b = ~B + 1'b1;
    else inp_b = B;

    if (sub && B == 4'b1000) begin
        // A - (-8) = A + 8; A is only in range from [-8, -1]. So, if A[3] = 0, there must be overflow in the positive direction
        if (A[3] == 0) begin
            ovfl = 1;
            S = 4'b0111;  // positive overflow saturation
        end else begin
            ovfl = 0;
            S = A + 4'b1000;    // S = A + 8
        end
    end else if (A[3] == inp_b[3] && A[3] != sum[3]) begin  // normal overflow, if A and B are the same sign but the sum is a different sign, there is overflow
        ovfl = 1;
        S = A[3] ? 4'b1000 : 4'b0111;
    end else begin  // no special case or overflow
        ovfl = 0;
        S = sum;
    end
end

endmodule