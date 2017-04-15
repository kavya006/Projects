import pygraphviz as pvg
from pygraphviz import *
from subprocess import call
import time
import graphviz as gv

def drawgraph1():
	A = AGraph(bgcolor="blanchedalmond")
	A.add_node("\n\nREVERSE-DELETE ALGORITHM",fontsize=24,fontcolor="darkslategray")
	A.add_node("Team Members:\n\n\nCS14B009 GOLLAMUDI NIKITHA \n\n CS14B046 KAVYA MRUDULA",fontsize=20,fontcolor="darkorchid4")
	A.add_edge("\n\nREVERSE-DELETE ALGORITHM","Team Members:\n\n\nCS14B009 GOLLAMUDI NIKITHA \n\n CS14B046 KAVYA MRUDULA")
	A.node_attr['shape'] = "none"
	A.edge_attr['style'] = "invisible" 
	A.write('simple.dot')
	graph = pvg.AGraph('simple.dot')
	graph.layout()
	graph.draw("1.jpg",prog="dot") #finished the graph
	call(["xdg-open", "1.jpg"])
	time.sleep(1)

def drawgraph2():
	A = AGraph(bgcolor="blanchedalmond")
	
	A.add_node("The Reverse-Delete Algorithm is an \nalgorithm in graph theory used to obtain \na minimum spanning tree from a given\n connected, edge-weighted graph.",fontsize=25)
	A.node_attr['shape'] = "none"
	A.node_attr['fontcolor'] = "darkslategray"
	A.node_attr['fontsize'] = 25
	A.write('simple.dot')
	graph = pvg.AGraph('simple.dot')
	graph.layout()
	graph.draw("1.jpg",prog="dot") #finished the graph
	call(["xdg-open", "1.jpg"])
	time.sleep(1)

def drawgraph3():
	A = AGraph(bgcolor="blanchedalmond",rankdir="LR")
	A.node_attr['shape']="box"
	A.add_node("4. Perform any deletion that does not\n lead to additional disconnection.",fontsize=16,fontcolor="darkorchid4",id=4)
	A.add_node("3. For each edge,\n check if deleting\n the edge will further\n disconnect the graph.",fontsize=16,fontcolor="darkorchid4",id=3)
	A.add_node("2. Go through E in decreasing order\n of edge weights.",fontcolor="darkorchid4",fontsize=16,id=2)
	A.add_node("1. Start with graph G, which \ncontains a list of edges E.",fontcolor="darkorchid4",fontsize=16,id=1)
	A.add_node("REVERSE-DELETE ALGORITHM \n\n The Algorithm Works as follows:",fontsize=20,fontcolor="darkslategray",shape="none")
	A.write('simple.dot')
	graph = pvg.AGraph('simple.dot')
	graph.layout()
	graph.draw("1.jpg",prog="dot")
	call(["xdg-open", "1.jpg"])
	time.sleep(1)

def drawgraph4():
	A = AGraph(bgcolor="blanchedalmond" ,rankdir="LR")
	A.add_node("3. Black -- this edge is not yet processed",fontcolor="black",fontsize=20)
	A.add_node("2. Red -- this edge is deleted\n",fontcolor="red",fontsize=20)
	A.add_node("1. Green -- this edge is in final output\n",fontcolor="green",fontsize=20)
	A.add_node("The color code used in the algorithm:",fontcolor="darkslategray",fontsize=22)
	A.node_attr['shape'] = "none"
	A.write('simple.dot')
	graph = pvg.AGraph('simple.dot')
	graph.layout()
	graph.draw("1.jpg",prog="dot")
	call(["xdg-open", "1.jpg"])
	time.sleep(1)

def drawgraph(num_ver, initgraph,outputgraph,value,tag1,tag2,count,tag3):
	if tag1 == 0:
		A = pvg.AGraph(forcelabels="true", rankdir="LR",bgcolor="blanchedalmond")
		A.node_attr['style']='filled'
		A.node_attr['shape']='circle'
		A.node_attr['penwidth'] = '2'
		A.node_attr['fixedsize']='true'
		A.node_attr['fontcolor']='#FFFFFF'
		A.node_attr['fillcolor']="#222222"
		A.edge_attr['penwidth'] = '2'
		A.edge_attr['color'] = "black"
		A.edge_attr['labeldistance'] = 3
		A.edge_attr['labelangle'] = 20
		if num_ver == 0:
			A.add_node("1")
			A.write('simple.dot')
			graph = pvg.AGraph('simple.dot',label="Test Case#"+str(count))
			graph.layout()
			graph.draw(str(count)+"final.jpg",prog="circo")
			call(["xdg-open", str(count)+".jpg"])
			time.sleep(1.4)
			return A
		for i in initgraph:
			if(i.weight != -1):
				A.add_edge(i.v1,i.v2,headlabel=str(i.value))
		if tag3 == 0:
			A.write('simple.dot')
			graph = pvg.AGraph('simple.dot',label="Test Case#" + str(count))
			graph.layout()
			graph.draw(str(count)+".jpg",prog="circo") #finished the graph
			call(["xdg-open", str(count)+".jpg"])
		else:
			A.edge_attr['len'] = "1"
			A.write('simple.dot')
			graph = pvg.AGraph('simple.dot',label="The Minimum Spanning Tree in Test Case# "+ str(count))
			graph.layout()
			graph.draw(str(count)+"final.jpg",prog="neato")
			call(["xdg-open", str(count)+"final.jpg"])
		time.sleep(1.4)
		return A 
	elif tag1 == 1:
		i = value
		if(i >= 0 and i < len(initgraph)):
			e = outputgraph.get_edge(initgraph[i].v1,initgraph[i].v2)
			n1 = outputgraph.get_node(initgraph[i].v1)
			n2 = outputgraph.get_node(initgraph[i].v2)
			if(tag2 == 0):
				if initgraph[i].weight == -1:	
					e.attr['color'] = "red"
					e.attr['style'] = "dashed"
					n1.attr['color'] = "lightcoral"
					n2.attr['color'] = "lightcoral"
					n1.attr['penwidth'] = 2
					n2.attr['penwidth'] = 2
			elif(tag2 == 1):
				if initgraph[i].tag == 1:	
					e = outputgraph.get_edge(initgraph[i].v1,initgraph[i].v2)
					e.attr['color'] = "green"
					e.attr['style'] = "solid"
					n1.attr['fillcolor'] = "cornflowerblue"
					n2.attr['fillcolor'] = "cornflowerblue"
					n1.attr['color'] = "black"
					n2.attr['color'] = "black"
		outputgraph.write('simple.dot')
		if tag2 == 0:
			graph = pvg.AGraph('simple.dot',label="Checking for a path between nodes \n"+str(initgraph[i].v1)+" and "+str(initgraph[i].v2)+" after deleting the edge "+str(initgraph[i].v1)+" ---> "+str(initgraph[i].v2))
		elif tag2 ==1:
			graph = pvg.AGraph('simple.dot',label="Edge "+str(initgraph[i].v1)+" ---> "+str(initgraph[i].v2)+" is a cut-edge" + "\n"+ "i.e. removal of the edge makes the graph \ndiscontinuous.Replacing the removed edge")
		graph.layout()
		graph.draw(str(count)+".jpg",prog="circo") #finished the graph
		call(["xdg-open", str(count)+".jpg"])
		time.sleep(2)
