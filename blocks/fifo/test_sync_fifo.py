"""
cocotb testbench for "sync_fifo" module

Run:  
    make
    make WAVES=1  (dump waves for GTKWave)
"""

import random

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD_NS = 10

# --------------------------------------------------------------------------- #
# model
# --------------------------------------------------------------------------- #

# golden model for FIFO buffer
class Queue:
    def __init__(self, depth):
        self.queue = []
        self.depth = depth
    
    def write(self, element):
        if self.isFull():
            return
        self.queue.append(element)

    def read(self):
        if self.isEmpty():
            return 0
        return self.queue.pop(0)

    def isEmpty(self):
        return int(len(self.queue) == 0)

    def isFull(self):
        return int(len(self.queue) == self.depth)

    def reset(self):
        self.queue.clear()

    # if needed, for debugging
    def size(self):
        return len(self.queue)

    def peek(self):
            if self.isEmpty():
                return "Queue is empty"
            return self.queue[0]

# --------------------------------------------------------------------------- #
# helpers
# --------------------------------------------------------------------------- #

def to_signed(value: int, width: int) -> int:
    """Interpret the low 'width' bits of 'value' as two's complement; used to convert n-bit representations into 32-bit Python int"""
    value &= (1 << width) - 1
    sign_bit = 1 << (width - 1)
    return (value - (1 << width)) if (value & sign_bit) else value

def to_unsigned(value: int, width: int) -> int:
    """Interpret the low 'width' bits of 'value' as unsigned int; used to convert 32-bit Python int to n-bit representation"""
    return value & ((1 << width) - 1)

def get_params(dut):
    """Read DEPTH / DATA_WIDTH from the elaborated DUT."""
    depth = int(dut.DEPTH.value)
    data_width = int(dut.DATA_WIDTH.value)
    return depth, data_width

async def start_clock(dut):
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD_NS, unit="ns").start())

async def reset_dut(dut, cycles: int = 2):
    """Assert active-low reset for `cycles`, then release on an edge."""
    dut.rst.value = 1
    dut.wr.value = 0
    dut.rd.value = 0
    dut.write_data.value = 0
    for _ in range(cycles):
        await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.rst.value = 0

async def step(dut, model: Queue, wr: int, rd: int, data_width: int, write_data: int = 0xFFFF, ctx: str = ""):
    """
    Drive one set of inputs and cross one clock edge, then check outputs

    Note that write_data defaults to 0xFFFF, won't be overwritten when wr = 0 (for debugging)
    """

    dut.wr.value = wr
    dut.rd.value = rd
    dut.write_data.value = to_unsigned(write_data, data_width)
    read_valid = not model.isEmpty()
    if wr: model.write(write_data)  # writing to model
    if rd and read_valid: exp_read_data = model.read()

    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")  # settle past the edge before anyone samples

    dut_read_data = to_signed(int(dut.read_data.value), data_width)
    dut_empty = int(dut.empty.value)
    dut_full = int(dut.full.value)

    prefix = f"[{ctx}] " if ctx else ""
    if rd and read_valid:
        assert dut_read_data == exp_read_data, (f"{prefix}read_data: dut={dut_read_data} exp={model.exp_read_data}")
    assert dut_empty == model.isEmpty(), (f"{prefix}empty: dut={dut_empty} exp={model.isEmpty()}")
    assert dut_full == model.isFull(), (f"{prefix}full: dut={dut_full} exp={model.isFull()}")


# --------------------------------------------------------------------------- #
# tests
# --------------------------------------------------------------------------- #

@cocotb.test()
async def test_reset(dut):
    """After reset, read_data and full = 0, empty = 1"""
    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    assert int(dut.read_data.value) == 0
    assert int(dut.empty.value) == 1
    assert int(dut.full.value) == 0

@cocotb.test()
async def test_write_read(dut):
    """Initialize empty, write once, read once"""
    depth, data_width = get_params(dut)
    model = Queue(depth)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    await step(dut, model, wr=1, rd=0, data_width=data_width, write_data=1, ctx="write")
    await step(dut, model, wr=0, rd=1, data_width=data_width, ctx="read")

@cocotb.test()
async def test_read_empty(dut):
    """Initialize empty, write once, read twice"""
    depth, data_width = get_params(dut)
    model = Queue(depth)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    model.reset()

    write_data = 1

    await step(dut, model, wr=1, rd=0, data_width=data_width, write_data=write_data, ctx="write")
    await step(dut, model, wr=0, rd=1, data_width=data_width, ctx="read")   # should return written data
    await step(dut, model, wr=0, rd=1, data_width=data_width, ctx="read")

@cocotb.test()
async def test_write_full(dut):
    """Writing until full, then writing again"""
    depth, data_width = get_params(dut)
    model = Queue(depth)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    model.reset()

    write_data = 1
    extra_data = 2

    # writing with write_data until full
    while not model.isFull():
        await step(dut, model, wr=1, rd=0, data_width=data_width, write_data=write_data, ctx="write")
    await step(dut, model, wr=1, rd=0, data_width=data_width, write_data=extra_data, ctx="write")    # writing one more time after full, with extra_data instead

    # reading until empty; the last read should return write_data, not extra_data
    while not model.isEmpty():
        await step(dut, model, wr=0, rd=1, data_width=data_width, ctx="read")

@cocotb.test()
async def test_simultaneous(dut):
    """
    Initialize empty, then run 3 cases:
    1. write and read on same cycle on an empty case; write should work but read should return 0
    2. write and read on same cycle on a non-empty, non-full case; both should work
    3. write until full then write and read on same cycle on full case; read should work but write shouldn't, tested by reading again
    """
    depth, data_width = get_params(dut)
    model = Queue(depth)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    model.reset()

    write_data = 1
    extra_data = 2

    # case 1: empty
    await step(dut, model, wr=1, rd=1, data_width=data_width, write_data=write_data, ctx="write-read")

    # case 2: non-empty (write from last case)
    await step(dut, model, wr=1, rd=1, data_width=data_width, write_data=write_data, ctx="write-read")

    # writing until full
    while not model.isFull():
        await step(dut, model, wr=1, rd=0, data_width=data_width, write_data=write_data, ctx="write")

    # case 3: full, writing with extra data
    await step(dut, model, wr=1, rd=1, data_width=data_width, write_data=extra_data, ctx="write-read")

    # reading until empty; the last read should return write_data, not extra_data
    while not model.isEmpty():
        await step(dut, model, wr=0, rd=1, data_width=data_width, ctx="read")

'''
@cocotb.test()
async def test_random_regression(dut):
    """Randomized valid/bubble mix"""
    data_width, acc_width = get_params(dut)
    model = PEModel(data_width, acc_width)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    model.reset()

    lo = -(1 << (data_width - 1))
    hi = (1 << (data_width - 1)) - 1

    for i in range(500):
        a = random.randint(lo, hi)
        b = random.randint(lo, hi)
        a_v = 1 if random.random() < 0.8 else 0
        b_v = 1 if random.random() < 0.8 else 0
        f = 1 if random.random() < 0.8 else 0
        await step(dut, a, b, in_a_valid = a_v, in_b_valid=b_v, in_first=f, data_width=data_width)
        model.step(a, b, in_a_valid = a_v, in_b_valid=b_v, in_first=f)
        check(dut, model, data_width, acc_width, ctx=f"rand[{i}]")
'''