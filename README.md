# CSCE-337-Project-1

Logic Circuit Schematic Beautifier

* Steps:
	1) Parse the net-list
	2) Convert the Verilog code to a DAG
	3) Construct graph 
	4) Draw graph

* Algorithms:
	= During research, we came across a paper that discusses Klass's algorithm that deals with 
	modeling circuits using DAGs. More research will be done regarding that aspect in order to 
	determine whether this algorithm or an alternative one will be used. 
	= As for topological sorting algorithms for building DAGs, we came across Kahn's algorithm, 
	which basically searches for vertices that have no edges and connects them to those that 
	have not been already listed.
	= Another topological sorting approach is based on the idea of reversing the postoder DFS 
	traversal of the graph.  

* Implementation Language:
	= Parsing will be done using Perl
	= Constructing the graph using C++
	= Draw graph using JavaScript

* Libraries:
	= Parsing the Verilog netlist will be done using the Perl library: Verilog::Netlist
	= For graphing on JavaScript, a library called Raphael and another called Dagre was found to draw cylic graphs. More research will be done regarding that. 


===========================================================

Milestone 2: Thursday, March 12, 2015 
* Topological Sorting Algorithm implemented (please refer to TopoSort.cpp): 
The code recieves the file that has the adjacency matrix and saves it in a 2D container (more specifically, a vector of vectors) with the name 'AdjList'. Then, the number of edges in per node is counted and saved in a vector 'Indegree', which specifies the number of connections internally within the graph. 
The AdjList and the Indegree vectors are passed to a 'TopoSort' function, which implements the Kahn algorithm for topological sorting as outlined on the provided link. After sorting is done, a check is done to ensure that no edges exist; if there are edges in the graph after the sorting, it means that the graph either had a node that was not in the graph or that the graph was cyclic. The result of this check is then reported to the main. 
