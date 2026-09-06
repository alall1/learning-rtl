module round_robin_arbiter #(
    parameter N = 4
)(
    input logic clk,
    input logic rst,
    input logic ack,                    // an acknowledgement from the granted master when done
    input logic [N-1:0] request_bus,    // a bus of requesters; priority MSB [high] -> LSB [low]
    output logic [N-1:0] grant_bus,     // grant bus; one-hot output
    output logic locked                 // grant is being asserted, arbiter locked until master asserts "ack"
);

logic [N-1:0] mask;

logic [N-1:0] higher_p_masked;
logic [N-1:0] grant_masked;

logic [N-1:0] higher_p_unmasked;
logic [N-1:0] grant_unmasked;

// combinationally finding grant for only (request_bus & mask), higher priority than the rest of request_bus
always_comb begin
    higher_p_masked[N-1] = 1'b0;
    for (int i = N-2; i >= 0; i--) higher_p_masked[i] = higher_p_masked[i+1] | (request_bus[i+1] & mask[i+1]);
    for (int i = 0; i < N; i++) grant_masked[i] = (request_bus[i] & mask[i]) & ~higher_p_masked[i];
end

// combinationally finding grant for request_bus; fallback if no grant in (request_bus & mask)
always_comb begin
    higher_p_unmasked[N-1] = 1'b0;
    for (int i = N-2; i >= 0; i--) higher_p_unmasked[i] = higher_p_unmasked[i+1] | request_bus[i+1];
    for (int i = 0; i < N; i++) grant_unmasked[i] = request_bus[i] & ~higher_p_unmasked[i];
end

// sequential logic of when grant_bus actually takes the value of grant_next and locked
always_ff @(posedge clk or posedge rst) begin
    if (rst) begin
        grant_bus <= '0;
        locked <= 1'b0;
        mask <= '1;
    end else if (ack) begin
        if (|(request_bus & mask)) begin
            grant_bus <= grant_masked;
            locked <= 1'b1;
        end else begin
            grant_bus <= grant_unmasked;
            if (|request_bus) locked <= 1'b1;
            else locked <= 1'b0;
        end
    end else if (~locked) begin
        if (|(request_bus & mask)) begin
            grant_bus <= grant_masked;
            locked <= 1'b1;
        end else begin
            grant_bus <= grant_unmasked;
            if (|request_bus) locked <= 1'b1;
        end
    end
    // no need for a else case; if none of the above are true, grant_bus and locked keep their values
end

endmodule