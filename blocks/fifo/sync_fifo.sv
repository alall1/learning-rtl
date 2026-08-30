module fifo #(
    parameter DEPTH = 4,
    parameter DATA_WIDTH = 8
)(
    input logic clk,
    input logic rst,
    input logic wr,
    input logic [DATA_WIDTH-1:0] write_data,
    input logic rd,
    output logic [DATA_WIDTH-1:0] read_data,
    output logic empty,
    output logic full
);

localparam int PTR_WIDTH = $clog2(DEPTH) + 1;   // calculating the number of bits the pointers should have, + 1 for the 'wrap' bit

logic [DATA_WIDTH-1:0] mem [0:DEPTH-1];         // initializing the element storage

logic [PTR_WIDTH-1:0] wr_ptr;                   // the write pointer; elements are written at this index if wr = 1
logic [PTR_WIDTH-1:0] rd_ptr;                   // the read pointer; elements are read from this index if rd = 1

assign empty = (wr_ptr == rd_ptr);  // empty: wrap bits equal, addr bits equal
assign full = ((wr_ptr[PTR_WIDTH-2:0] == rd_ptr[PTR_WIDTH-2:0]) && (wr_ptr[PTR_WIDTH-1] != rd_ptr[PTR_WIDTH-1])); // full: wrap bits not equal, addr bits equal

always_ff @(posedge clk or posedge rst) begin
    if (rst) begin
        wr_ptr <= '0;
        rd_ptr <= '0;
    end else begin
        if (wr) begin
            if (full) begin     // FIFO full
                wr_ptr <= wr_ptr;
            end else begin
                if (wr_ptr == DEPTH - 1) begin
                    wr_ptr[PTR_WIDTH-2:0] <= '0;
                    wr_ptr[PTR_WIDTH-1] <= ~wr_ptr[PTR_WIDTH-1];
                end else begin
                    wr_ptr <= wr_ptr + 1;
                end
                mem[wr_ptr[PTR_WIDTH-2:0]] <= write_data;
            end
        end
        if (rd) begin
            if (empty) begin    // FIFO empty
                rd_ptr <= rd_ptr;
            end else begin
                if (rd_ptr == DEPTH - 1) begin
                    rd_ptr[PTR_WIDTH-2:0] <= '0;
                    rd_ptr[PTR_WIDTH-1] <= ~rd_ptr[PTR_WIDTH-1];
                end else begin
                    rd_ptr <= rd_ptr + 1;
                end
                read_data <= mem[rd_ptr[PTR_WIDTH-2:0]];
            end
        end
    end
end

endmodule