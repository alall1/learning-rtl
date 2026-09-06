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

logic [N-1:0] higher_p;
logic [N-1:0] grant_next;

// combinationally finding the one-hot grant output based on the current request_bus
always_comb begin
    higher_p[N-1] = 1'b0;
    for (int i = N-2; i >= 0; i--) higher_p[i] = higher_p[i+1] | request_bus[i+1];
    for (int i = 0; i < N; i++) grant_next[i] = request_bus[i] & ~higher_p[i];
end

// sequential logic of when grant_bus actually takes the value of grant_next and locked
always_ff @(posedge clk or posedge rst) begin
    if (rst) begin
        grant_bus <= '0;
        locked <= 1'b0;
    end else if (ack) begin
        grant_bus <= grant_next;
        if (|request_bus) locked <= 1'b1;
        else locked <= 1'b0;
    end else if (|request_bus && ~locked) begin
        grant_bus <= grant_next;
        locked <= 1'b1;
    end
    // no need for a else case; if none of the above are true, grant_bus and locked keep their values
end

endmodule