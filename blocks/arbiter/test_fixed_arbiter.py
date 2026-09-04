"""
cocotb testbench for "fixed_arbiter" module

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

# golden model for fixed-priority arbiter
class Arbiter:
    def __init__(self, N):
        self.grant = 0
        self.locked = 0
        self.N = N
    
    def reset(self):
        self.grant = 0
        self.locked = 0

    def step(self, request_bus, ack):
        if request_bus > (2 ** (self.N)) - 1: raise ValueError("request_bus out of range")
        if (ack):
            self.locked = 0
        if request_bus != 0 and self.locked == 0:
            i = request_bus.bit_length() - 1    # index of granter
            self.grant = 1 << i
            self.locked = 1

# --------------------------------------------------------------------------- #
# helpers
# --------------------------------------------------------------------------- #

def to_unsigned(value: int, width: int) -> int:
    """Interpret the low 'width' bits of 'value' as unsigned int; used to convert 32-bit Python int to n-bit representation"""
    return value & ((1 << width) - 1)

def get_params(dut):
    """Read DEPTH / DATA_WIDTH from the elaborated DUT."""
    N = int(dut.N.value)
    return N

async def start_clock(dut):
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD_NS, unit="ns").start())

async def reset_dut(dut, cycles: int = 2):
    """Assert active-low reset for `cycles`, then release on an edge."""
    
    dut.rst.value = 1
    dut.ack.value = 0
    dut.request_bus.value = 0
    for _ in range(cycles):
        await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.rst.value = 0

async def step(dut, model: Arbiter, request_bus: int, ack: int = 0, ctx: str = ""):
    """
    Drive one set of inputs and cross one clock edge, then check outputs
    """

    dut.ack.value = ack
    dut.request_bus.value = request_bus

    model.step(request_bus, ack)

    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")  # settle past the edge before anyone samples

    dut_grant_bus = int(dut.grant_bus.value)
    dut_locked = int(dut.locked.value)

    prefix = f"[{ctx}] " if ctx else ""
    assert dut_grant_bus == model.grant, (f"{prefix}_grant_bus: dut={dut_grant_bus} exp={model.grant}")
    assert dut_locked == model.locked, (f"{prefix}_locked: dut={dut_locked} exp={model.locked}")

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

    assert int(dut.grant_bus.value) == 0
    assert int(dut.locked.value) == 0

@cocotb.test()
async def test_request_ack(dut):
    """Assert grant, hold for a few cycles, then ack; one time"""
    N = get_params(dut)
    model = Arbiter(N)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    NUM_CYCLES = 10

    max = (2 ** N) - 1
    req_bus = random.randint(1, max)    # random integer between 1 and 2^N - 1; always asserting a request
    garbage = random.randint(1, max)    # random integer between 1 and 2^N - 1; garbage value that SHOULDN'T be picked up, while locked=1

    await step(dut, model, request_bus=req_bus, ctx="req")     # requests come in as req_bus

    for i in range(NUM_CYCLES):
        await step(dut, model, request_bus=garbage, ctx=f"garbage#{i}") # garbage requests come in, ack not asserted so model is still locked

    await step(dut, model, request_bus=0, ack=1, ctx="ack")    # no requests, ack asserted -> locked = 0

@cocotb.test()
async def test_consec_request(dut):
    """Testing consecutive requests + acks"""
    N = get_params(dut)
    model = Arbiter(N)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    NUM_CYCLES = 50

    max = (2 ** N) - 1
    for i in range(NUM_CYCLES):
        req_bus = random.randint(1, max)    # random integer between 1 and 2^N - 1; always asserting a request
        await step(dut, model, request_bus=req_bus, ack=1, ctx=f"req-ack#{i}")     # requests come in as req_bus

# @cocotb.test()
# async def test_random(dut):
#     """
#     Randomized test: drive random wr/rd each cycle over many cycles, checking read_data, full, and empty against the golden model every edge.
#     Catches wrap bugs at arbitrary addresses, corner cases at full/empty, and simultaneous rd+wr interactions. Run with a non-power-of-two DEPTH
#     (e.g. 6) to also exercise the wrap-bit path.
#     """
#     depth, data_width = get_params(dut)
#     model = Queue(depth)

#     NUM_CYCLES = 5000
#     seed = random.randrange(1 << 32)
#     random.seed(seed)
#     dut._log.info(f"test_random seed={seed} depth={depth} data_width={data_width}")

#     await start_clock(dut)
#     await reset_dut(dut)
#     await RisingEdge(dut.clk)
#     await Timer(1, unit="ns")
#     model.reset()

#     mask = (1 << data_width) - 1
#     val = 0

#     for i in range(NUM_CYCLES):
#         wr = random.randint(0, 1)
#         rd = random.randint(0, 1)
#         # fresh, unique-ish data each write so ordering errors are visible
#         val = (val + 1) & mask
#         await step(dut, model, wr=wr, rd=rd, data_width=data_width, write_data=val, ctx=f"rand#{i} wr={wr} rd={rd}")