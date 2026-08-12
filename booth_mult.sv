module booth_mult (
    input logic [3:0] A,
    input logic [3:0] B,
    output logic [7:0] S
);

logic [8:0] reg;    // register that contains accumulator (top 4 bits), Q (next 4 bits) and Q (last bit). Result is bits [8:1] after results
logic [3:0] acc;    // accumulator, top 4 bits of result
logic [3:0] Q;      // Q, starts as multiplier B then becomes bottom 4 bits of result
logic Qlast;        // Qlast, the Q(-1) bit, or the last bit before Q was arithmetically shifted right

endmodule