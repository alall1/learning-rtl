module addsub_4bit (
    input logic [3:0] A,
    input logic [3:0] B,
    output logic [3:0] S,
    output logic ovfl
);

logic Cout;
logic [3:0] sum;

ripple_adder_4bit ra (.A(A), .B(B), .S(sum), .Cout(Cout));

always_comb begin
    if (ra.c2 == Cout) begin    // comparing carry-in vs carry-out of the MSB to determine if there is overflow or not
        ovfl = 1;
        // saturating if there is overflow
        if (sum[3] == 0) S = 4'b1000;   // two negative numbers being added to create a negative number out-of-range (hardware wraps it around to be positive)
        else S = 4'b1111;               // two 
    end else begin
        ovfl = 0;
        S = sum;    // if no overflow, S = sum as usual
    end
end

endmodule