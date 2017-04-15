class edge:
	"""docstring for ClassName"""
	def __init__(self, v1, v2, weight):
		self.v1 = v1
		self.v2 = v2
		self.weight = weight
		self.tag=0
		self.value=weight
	def __cmp__(self, e):
		if self.weight > e.weight:
			return -1
		if self.weight < e.weight:
			return 1
		return 0
	def __repr__(self):
		return "{}: {} {} {}". format(self.__class__.__name__, self.v1, self.v2, self.weight)
	def cmp (self,e):
		if self.v1 > e.v1:
			return 1
		elif self.v1 < e.v1:
			return -1
		else:
			if self.v2 > e.v2:
				return 1
			if self.v2 < e.v2:
				return -1
			return 0

class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)


