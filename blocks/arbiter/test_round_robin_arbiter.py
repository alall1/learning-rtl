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
class fixedArbiter:
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
            self.grant = 0
        if request_bus != 0 and self.locked == 0:
            i = request_bus.bit_length() - 1    # index of granter
            self.grant = 1 << i
            self.locked = 1

# golden model for fixed-priority arbiter
class roundRobinArbiter:
    def __init__(self, N):
        self.grant = 0
        self.locked = 0
        self.mask = (2 ** (N)) - 1     # all 1s
        self.masked = fixedArbiter(N)
        self.unmasked = fixedArbiter(N)
        self.N = N
    
    def reset(self):
        self.grant = 0
        self.locked = 0
        self.mask = (2 ** (self.N)) - 1
        self.masked.reset()
        self.unmasked.reset()

    def step(self, request_bus, ack):
        if request_bus > (2 ** (self.N)) - 1: raise ValueError("request_bus out of range")

        if (ack):
            self.locked = 0
            self.grant = 0

        self.masked.step(request_bus & self.mask, 1)
        self.unmasked.step(request_bus, 1)

        grant_masked = self.masked.grant
        grant_unmasked = self.unmasked.grant

        if self.locked == 0:
            if request_bus:
                self.mask = self.grant - 1
                self.locked = 1
                self.grant = grant_masked
            else:
                self.grant = grant_unmasked

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

async def step(dut, model: roundRobinArbiter, request_bus: int, ack: int = 0, ctx: str = ""):
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
    """After reset, locked = 0 and grant_bus = 0"""
    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    assert int(dut.grant_bus.value) == 0
    assert int(dut.locked.value) == 0

@cocotb.test()
async def test_empty_request(dut):
    """Testing consecutive empty requests"""
    N = get_params(dut)
    model = roundRobinArbiter(N)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    NUM_CYCLES = 10

    for i in range(NUM_CYCLES):
        await step(dut, model, request_bus=0, ack=1, ctx=f"empty-req#{i}")

@cocotb.test()
async def test_consecutive_full(dut):
    """Testing consecutive full request buses; grant should change each cycle (round-robin)"""
    N = get_params(dut)
    model = roundRobinArbiter(N)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    NUM_CYCLES = 10

    max = (2 ** N) - 1
    for i in range(NUM_CYCLES):
        req_bus = random.randint(1, max)    # random integer between 1 and 2^N - 1; always asserting a request
        await step(dut, model, request_bus=req_bus, ack=1, ctx=f"req-ack#{i}")     # requests come in as req_bus

@cocotb.test()
async def test_request_ack(dut):
    """Assert grant, hold for a few cycles, then ack; one time"""
    N = get_params(dut)
    model = roundRobinArbiter(N)

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
async def test_simultaneous_req_ack(dut):
    """Testing consecutive requests + acks"""
    N = get_params(dut)
    model = roundRobinArbiter(N)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    NUM_CYCLES = 10

    max = (2 ** N) - 1
    for i in range(NUM_CYCLES):
        req_bus = random.randint(1, max)    # random integer between 1 and 2^N - 1; always asserting a request
        await step(dut, model, request_bus=req_bus, ack=1, ctx=f"req-ack#{i}")     # requests come in as req_bus

@cocotb.test()
async def test_random(dut):
    """Testing random inputs"""
    N = get_params(dut)
    model = roundRobinArbiter(N)

    await start_clock(dut)
    await reset_dut(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    NUM_CYCLES = 100

    max = (2 ** N) - 1

    for i in range(NUM_CYCLES):
        ack = random.randint(0, 1)          # random chance of 0 or 1
        req_bus = random.randint(0, max)    # random integer between 0 and 2^N - 1; could be empty
        await step(dut, model, request_bus=req_bus, ack=ack, ctx=f"rand#{i}")     # requests come in as req_bus