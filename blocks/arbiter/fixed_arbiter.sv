module fixed_arbiter #(
    parameter N = 4
)(
    input logic clk,
    input logic rst,
    input logic ack,                    // an acknowledgement from the granted master when done
    input logic [N-1:0] request_bus,    // a bus of requesters; priority MSB [high] -> LSB [low]
    output logic [N-1:0] grant_bus,     // grant bus; one-hot output
    output logic locked                 // grant is being asserted, arbiter locked until master asserts "ack"
);

always_ff @(posedge clk or posedge rst) begin
    if (rst) begin
        grant_bus <= '0;
        locked <= 1'b0;
    end else begin
        if (ack) locked <= 1'b0;    // granted master done; re-arbitrate
        if (|req && ~locked) begin
            // grant logic
            locked <= 1'b1;
        end
    end
end

endmodule