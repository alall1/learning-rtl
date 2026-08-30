
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

model = Queue(8)
print(model.queue)
print(model.isEmpty())
print(model.isFull())
model.write(5)
print(model.queue)
print(model.isEmpty())
print(model.isFull())
model.read()
print(model.queue)
print(model.isEmpty())
print(model.isFull())