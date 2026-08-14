module booth_mult (
    input logic clk,
    input logic rst,
    input logic [3:0] M,
    input logic [3:0] Q,
    output logic signed [7:0] P
);

logic [8:0] r;              // register that contains accumulator (top 4 bits), Q (next 4 bits) and Q (last bit). Result is bits [8:1] after results
logic [3:0] acc;     // accumulator, top 4 bits of result; signed because acc adds M (or -M) to itself 
logic [3:0] Qr;             // Qr, starts as multiplier Q inside of r
logic Qlast;                // Qlast, the Q(-1) bit, or the last bit before Q was arithmetically shifted right
logic signed [3:0] Mneg;    // -M

logic [2:0] count;  // count of the clock cycles (0, 1, 2, 3, 4)

assign Mneg = -M;   // setting Mneg = -M, would already become signed but already declared as a signed bus

always_comb begin
    Qr = r[4:1];     // Q will always be equal to 
    Qlast = r[0];
    case (r[1:0])       // different cases for Qlsb and Qlast
        2'b00, 2'b11: acc = r[8:5];     // only ARS, registers retain values (gets ARS in always_ff)
        2'b01: acc = r[8:5] + M;        // acc = acc + (-M); could have just done acc = acc - M but Mneg to closer match the logic I am implementing
        2'b10: acc = r[8:5] + Mneg;     // acc = acc + M;
        default: acc = 4'b0000;         // default case, if r = XXX (Verilator doesn't simulate this)
    endcase
end

always_ff @(posedge clk) begin
    if (rst) begin
        r <= {4'b0000, Q, 1'b0};
        count <= 3'b000;
        // $display("RESET committing r=%b", {4'b0000, 4'b1000, 1'b0});
    end else if (count != 3'b100) begin       // count is maxed, stops operations
        r <= $signed({acc, r[4:0]}) >>> 1;    // update r with new acc, Q, Qlast, arithmetic shifted right, because ARS happens at the end of every case
        count <= count + 1;
    end
end

assign P = r[8:1];  // constantly assigning S = top 8 bits of R, will be result when "done" is high

endmodule