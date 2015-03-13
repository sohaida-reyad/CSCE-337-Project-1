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
The code recieves the file that has the adjacency matrix and saves it in a 2D container (more specifically, a vector of vectors) with the name 'AdjMatrix'. Then, the number of edges in per node is counted and saved in a vector 'Edge', which specifies the number of connections internally within the graph. 
The AdjMatrix and the Edge vectors are passed to a 'TopoSort' function, which implements the Kahn algorithm for topological sorting as outlined on the provided link. After sorting is done, a check is done to ensure that no edges exist; if there are edges in the graph after the sorting, it means that the graph either had a node that was not in the graph or that the graph was cyclic. The result of this check is then reported to the main in the vector with the name 'SortedList'. 
The implementation of the Topological Algorithm in the project was based on Kahn's algorithm. The implemented code was based on the pseuodcode in the following link:
http://en.wikipedia.org/wiki/Topological_sorting


As for parsing the gate level netlist using perl:
1 - We started with installing perl. 
We followed this tutorial 
http://www.tutorialspoint.com/perl/perl_environment.htm
for installing perl, IDE for perl and learning and playing with the basics of perl

2- We wanted to install the perl verilog library, we found it easier to install it on linux. 
We installed the library with the help of this link.
http://www.veripool.org/projects/verilog-perl/wiki/Installing

3- We then began to read the different classes of the perl verilog, found that probably we will use Verilog::Netlist, Verilog::Netlist::Cell, Verilog::Netlist::Module, Verilog::Netlist::Cell

4- We created a simple perl file "test1.pl" to parse the "booth.g.v" file ( one of the test files). The code was based on the example from this tutorial:
http://search.cpan.org/dist/Verilog-Perl/Netlist.pm

However it has compilation errors, after spending some time in trying to figure out what is wrong, we figured out that it does not read the file correctly so as to be able to identify the modules correctly. 

We have a question:
- Each file will have only one module, right ?
