module addsub_4bit #(
    parameter int WIDTH = 6
)(
    input logic signed [WIDTH-1:0] A,
    input logic signed [WIDTH-1:0] B,
    output logic [WIDTH-1:0] S,
    output logic ovfl
);

logic signed [WIDTH:0] sum_ext;

always_comb begin
    sum_ext = A + B;
    if (sum_ext > (2**(WIDTH-1) - 1)) begin          // if sum is greater than 2^(WIDTH-1) - 1, overflowing positively
        ovfl = 1;
    end else if (sum_ext < -(2**(WIDTH-1))) begin    // if sum is greater than 2^(WIDTH-1), overflowing negatively
        ovfl = 1;
    end else begin
        ovfl = 0;
    end
    S = sum_ext[WIDTH-1:0];
end

endmodule