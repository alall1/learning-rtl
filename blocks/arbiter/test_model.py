
# golden model for FIFO buffer
class arbiter:
    def __init__(self, N):
        self.grant = 0
        self.grant_valid = 0
        self.locked = 0
    
    def reset(self):
        self.grant = 0
        self.grant_valid = 0
        self.locked = 0

    def step(self, request_bus, ack):
        if (ack):
            self.locked = 0
        if request_bus != 0 and locked == 0:
            i = request_bus.bit_length() - 1    # index of granter
            self.grant = 1 << i
            self.locked = 1

# model = Queue(8)
# print(model.queue)
# print(model.isEmpty())
# print(model.isFull())
# model.write(5)
# print(model.queue)
# print(model.isEmpty())
# print(model.isFull())
# model.read()
# print(model.queue)
# print(model.isEmpty())
# print(model.isFull())