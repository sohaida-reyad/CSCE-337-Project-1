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


