import numpy
from drawGraph import * 
from edge import *

def bfs(matrix, source, sink):
	visited = []
	queue = Queue() 
	for i in range (0, matrix.shape[0]):
		visited.append(0)
	visited[source] = 1
	queue.enqueue(source)
	while (queue.size() !=  0):
		currnode = queue.dequeue()
		visited[currnode] = 1
		if currnode == sink :
			return 1
		for i in range (0, matrix.shape[0]):
			if(matrix[currnode,i] == 1 and visited[i] == 0):
				queue.enqueue(i)
	return 0

def reverseDelete(matrix,graph,num_ver,count):
	if count == 1:
		drawgraph1()
		drawgraph2()
		drawgraph3()
		drawgraph4()
	if num_ver == 0:
		A = drawgraph(num_ver,graph,0,0,0,0,count,0)
	graph.sort()
	A = drawgraph(num_ver,graph,0,0,0,0,count,0)
	for i in range(0, len(graph)):
		e = graph[i].weight
		graph[i].weight = -1
		drawgraph(num_ver,graph,A,i,1,0,count,0)
		matrix[graph[i].v1,graph[i].v2] = 0
		matrix[graph[i].v2, graph[i].v1] = 0
		if bfs(matrix, graph[i].v1, graph[i].v2) == 0 :
			graph[i].weight = e
			matrix[graph[i].v1, graph[i].v2] = 1
			matrix[graph[i].v2, graph[i].v1] = 1
			graph[i].tag=1
			drawgraph(num_ver,graph,A,i,1,1,count,0)
	drawgraph(num_ver,graph,A,0,0,0,count,1)



"""
print "reverseDeleted graph"
for i in  range(0,len(graph)):
	print graph[i]
"""



  
