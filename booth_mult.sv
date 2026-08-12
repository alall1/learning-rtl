module booth_mult (
    input logic clk,
    input logic [3:0] A,
    input logic [3:0] B,
    output logic [7:0] S
);

logic [8:0] r;      // register that contains accumulator (top 4 bits), Q (next 4 bits) and Q (last bit). Result is bits [8:1] after results
logic [3:0] acc;    // accumulator, top 4 bits of result
logic [3:0] Q;      // Q, starts as multiplier B then becomes bottom 4 bits of result
logic Qlast;        // Qlast, the Q(-1) bit, or the last bit before Q was arithmetically shifted right

logic [1:0] count;  // count of the clock cycles (0, 1, 2, 3)

always_comb begin
    case (r[1:0])       // different cases for Qlsb and Qlast
        2'b00, 2'b11: begin     // only ARS, registers retain values (gets ARS in always_ff)
            acc = r[8:5];
            Q = r[4:1];
            Qlast = r[0];
        end

        2'b01: begin

        end

        2'b10: begin

        end

        default: begin

        end

    endcase
    acc = count
end

always_ff @(posedge clk) begin
    if (count == 2'b11) begin       // count is maxed, stops operations
        S <= r[8:1];
    end else begin
        r <= $signed({acc, Q, Qlast}) >>> 1;    // update r with new acc, Q, Qlast, arithmetic shifted right, because ARS happens at the end of every case
    end
end

endmodule