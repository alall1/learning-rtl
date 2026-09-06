
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
        print(f"{request_bus:04b}")
        print(f"{self.mask:04b}")
        if request_bus > (2 ** (self.N)) - 1: raise ValueError("request_bus out of range")

        if (ack):
            self.locked = 0
            self.grant = 0

        self.masked.step(request_bus & self.mask, 1)
        self.unmasked.step(request_bus, 1)

        grant_masked = self.masked.grant
        grant_unmasked = self.unmasked.grant

        if self.locked == 0:
            self.grant = grant_masked if request_bus & self.mask else grant_unmasked
            self.locked = 1

        self.mask = self.grant - 1

# model = roundRobinArbiter(4)
# model.step(15, 1)
# print(f"1. grant: {model.grant}, locked: {model.locked}")
# model.step(15, 1)
# print(f"2. grant: {model.grant}, locked: {model.locked}")
# model.step(12, 1)
# print(f"3. grant: {model.grant}, locked: {model.locked}")
# model.step(15, 1)
# print(f"4. grant: {model.grant}, locked: {model.locked}")
# model.step(15, 1)
# print(f"5. grant: {model.grant}, locked: {model.locked}")
# model.step(15, 1)
# print(f"6. grant: {model.grant}, locked: {model.locked}")
# model.step(15, 1)
# print(f"7. grant: {model.grant}, locked: {model.locked}")