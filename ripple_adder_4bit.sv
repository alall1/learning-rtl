module ripple_adder_4bit (
    input logic [3:0] A,
    input logic [3:0] B,
    output logic [3:0] S,
    output logic Cout
);

logic c0, c1, c2;

carry_in_adder a0 (.A(A[0]), .B(B[0]), .Cin(1'b0), .S(S[0]), .Cout(c0));
carry_in_adder a1 (.A(A[1]), .B(B[1]), .Cin(c0), .S(S[1]), .Cout(c1));
carry_in_adder a2 (.A(A[2]), .B(B[2]), .Cin(c1), .S(S[2]), .Cout(c2));
carry_in_adder a3 (.A(A[3]), .B(B[3]), .Cin(c2), .S(S[3]), .Cout(Cout));

endmodule
