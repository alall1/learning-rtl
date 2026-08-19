module param_adder #(
    parameter int WIDTH = 10
)(
    input logic signed [WIDTH-1:0] A,
    input logic signed [WIDTH-1:0] B,
    output logic [WIDTH-1:0] S,
    output logic ovfl
);

logic signed [WIDTH:0] sum_ext;

always_comb begin
    sum_ext = {A[WIDTH-1], A} + {B[WIDTH-1], B};

    /* Verilog only does arithmetic "(2**(WIDTH-1) - 1)" up to 32 bits, errors after
    
    if (sum_ext > (2**(WIDTH-1) - 1)) begin          // if sum is greater than 2^(WIDTH-1) - 1, overflowing positively
        ovfl = 1;
    end else if (sum_ext < -(2**(WIDTH-1))) begin    // if sum is greater than 2^(WIDTH-1), overflowing negatively
        ovfl = 1;
    end else begin
        ovfl = 0;
    end

    */

    // a better way to check for overflow is by comparing sign bits of inputs and output

    // debugging: $display("A=%b Amsb=%b sum_ext=%b ovf_terms=%b%b", A, A[WIDTH-1], sum_ext, (A[WIDTH-1]==B[WIDTH-1]), (A[WIDTH-1]!=sum_ext[WIDTH-1]));

    if (A[WIDTH-1] == B[WIDTH-1] && A[WIDTH-1] != sum_ext[WIDTH-1] && A[WIDTH-1] == 1) begin        // negative inputs, positive output -> negative overflow
        ovfl = 1;
        S = {1'b1, {(WIDTH-1){1'b0}}};
    end else if (A[WIDTH-1] == B[WIDTH-1] && A[WIDTH-1] != sum_ext[WIDTH-1] && A[WIDTH-1] == 0) begin    // positive inputs, negative output -> positive overflow
        ovfl = 1;
        S = {1'b0, {(WIDTH-1){1'b1}}};
    end else begin
        ovfl = 0;
        S = sum_ext[WIDTH-1:0];
    end

end

endmodule