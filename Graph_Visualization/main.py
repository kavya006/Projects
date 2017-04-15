import numpy
from reverseDelete import *
from edge import *

f = open('input.txt')
T = int (f.readline().strip())
for j in range(0,T):
	n = int (f.readline().strip())
	graph = []
	matrix = numpy.zeros((n+1, n+1) , dtype = int)
	num_ver = 0
	for i in range (0,n):
		v1,v2,weight = map(int, f.readline().strip().split())
		matrix[v1,v2] = 1
		matrix[v2,v1] = 1
		num_ver = max(v1,v2,num_ver)
		graph.append(edge(min(v1,v2),max(v1,v2),weight))
	graph.sort(edge.cmp)
	reverseDelete(matrix,graph,num_ver,j+1)
	f.readline()
