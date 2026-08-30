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
    if rd and read_valid: exp_read_data = to_unsigned(model.read(), data_width)

    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")  # settle past the edge before anyone samples

    dut_read_data = int(dut.read_data.value)
    dut_empty = int(dut.empty.value)
    dut_full = int(dut.full.value)

    prefix = f"[{ctx}] " if ctx else ""
    if rd and read_valid:
        assert dut_read_data == exp_read_data, (f"{prefix}read_data: dut={dut_read_data} exp={exp_read_data}")
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

@cocotb.test()
async def test_wraparound_laps(dut):
    """
    Drive interleaved writes/reads across multiple laps so the pointer wraps while the wrap bit is set. Exposes wrap-bit comparison bug (comparing the full pointer to DEPTH, instead of comparing only the address bits of the pointer),
    which only manifests after >2*DEPTH cumulative writes. Requires a non-power-of-two DEPTH to catch it (power-of-two hides it via natural overflow) — run this with DEPTH=6.
    """
    depth, data_width = get_params(dut)
    model = Queue(depth)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    model.reset()

    # Enough cumulative writes to lap the pointer at least 3 times: keep the FIFO partially filled so both pointers keep advancing.
    # Pattern: write 2, read 1, repeat. Net +1 per iteration until near full, with steady pointer motion through many wraps.
    val = 0
    total_writes = 0
    target_writes = 4 * depth + 2   # comfortably past 2*DEPTH, into 3rd+ lap

    while total_writes < target_writes:
        # write if not full
        if not model.isFull():
            val = (val + 1) & ((1 << data_width) - 1)
            await step(dut, model, wr=1, rd=0, data_width=data_width,
                       write_data=val, ctx=f"w{total_writes}")
            total_writes += 1
        # read if not empty (drain one to keep pointers moving)
        if not model.isEmpty():
            await step(dut, model, wr=0, rd=1, data_width=data_width,
                       ctx=f"r{total_writes}")

    # drain and confirm ordering intact after all the wrapping.
    while not model.isEmpty():
        await step(dut, model, wr=0, rd=1, data_width=data_width, ctx="drain")

@cocotb.test()
async def test_random(dut):
    """
    Randomized test: drive random wr/rd each cycle over many cycles, checking read_data, full, and empty against the golden model every edge.
    Catches wrap bugs at arbitrary addresses, corner cases at full/empty, and simultaneous rd+wr interactions. Run with a non-power-of-two DEPTH
    (e.g. 6) to also exercise the wrap-bit path.
    """
    depth, data_width = get_params(dut)
    model = Queue(depth)

    NUM_CYCLES = 5000
    seed = random.randrange(1 << 32)
    random.seed(seed)
    dut._log.info(f"test_random seed={seed} depth={depth} data_width={data_width}")

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    model.reset()

    mask = (1 << data_width) - 1
    val = 0

    for i in range(NUM_CYCLES):
        wr = random.randint(0, 1)
        rd = random.randint(0, 1)
        # fresh, unique-ish data each write so ordering errors are visible
        val = (val + 1) & mask
        await step(dut, model, wr=wr, rd=rd, data_width=data_width, write_data=val, ctx=f"rand#{i} wr={wr} rd={rd}")