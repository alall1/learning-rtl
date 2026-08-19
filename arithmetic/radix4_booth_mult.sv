module radix4_booth_mult (
    input logic clk,
    input logic rst,
    input logic [4:0] M,
    input logic [4:0] Q,
    output logic signed [9:0] P
);

logic [13:0] r;             // 14-bit register {acc, Qext, Qlast}
logic [6:0] acc;            // accumulator, 7 bits (to account for 2M and -2M)
logic [5:0] Qext;           // since Q is an odd number of bits, sign-extend to the nearest even number of bits (6)
logic [6:0] Mext, Mneg;     // sign-extended M and negative M (7 bits to match width of acc)
logic [6:0] d_Mext, d_Mneg; // double Mext and Mneg, for 2M and -2M

logic [1:0] count;          // count of the clock cycles (0, 1, 2, 3)

always_comb begin           // for precomputing Mext, -M, 2M, -2M, Qext
    Qext = {Q[4], Q};
    Mext = {M[4], M[4], M};
    Mneg = -Mext;
    d_Mext = Mext << 1;
    d_Mneg = Mneg << 1;
end

always_comb begin
    case (r[2:0])                               // different cases for Q+1, Qlsb, Q-1
        3'b000, 3'b111: acc = r[13:7];          // only 2x ARS, registers retain values (ARS in always_ff)
        3'b001, 3'b010: acc = r[13:7] + Mext;   // acc = acc + M
        3'b101, 3'b110: acc = r[13:7] + Mneg;   // acc = acc + (-M)
        3'b011: acc = r[13:7] + d_Mext;         // acc = acc + 2M
        3'b100: acc = r[13:7] + d_Mneg;         // acc = acc + (-2M)
        default: acc = 7'b0000000;              // default case, if r[2:0] = XXX
    endcase
end

always_ff @(posedge clk) begin
    if (rst) begin
        r <= {7'b00000, Qext, 1'b0};
        count <= 2'b00;
        // $display("RESET committing r=%b", {4'b0000, 4'b1000, 1'b0});
    end else if (count != 2'b11) begin
        r <= $signed({acc, r[6:0]}) >>> 2;  // update r with new acc; 2x ARS
        count <= count + 1;
    end
end

assign P = r[10:1];     // 5-bit inputs = 10 bit result

endmodule