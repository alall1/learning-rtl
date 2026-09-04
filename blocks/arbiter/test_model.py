
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

model = Arbiter(4)
print(f"1. grant: {model.grant}, locked: {model.locked}")
model.step(1, 0)
print(f"2. grant: {model.grant}, locked: {model.locked}")
model.step(2, 0)
print(f"3. grant: {model.grant}, locked: {model.locked}")
model.step(0, 1)
print(f"4. grant: {model.grant}, locked: {model.locked}")
model.step(8, 1)
print(f"5. grant: {model.grant}, locked: {model.locked}")
model.step(15, 1)
print(f"6. grant: {model.grant}, locked: {model.locked}")
model.step(0, 0)
print(f"7. grant: {model.grant}, locked: {model.locked}")
model.step(0, 1)
print(f"8. grant: {model.grant}, locked: {model.locked}")


