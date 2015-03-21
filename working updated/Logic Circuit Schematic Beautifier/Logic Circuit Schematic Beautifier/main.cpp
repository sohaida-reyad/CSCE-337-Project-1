//
//  main.cpp
//  Logic Circuit Schematic Beautifier
//
//  Created by Mac on 3/21/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

/*
#include <iostream>

using namespace std;

//int main(int argc, const char * argv[]) {
int main() {
    
    return 0;
}
 */

//
//  main.cpp
//  DAG
//
//  Created by Mac on 3/20/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#include <iostream>
#include <string>

#include "DAG.h"
#include "gate.h"
#include "TopoSort.h"

using namespace std;

//int main(int argc, const char * argv[]) {
int main() {
    DAG netlist;
    gate * g, * g1;
    
    string file = "//Users//mac//Desktop//folder//parsed_2b_adder.g.v.txt";
    
    unsigned int numberGates;
    
    //if (netlist->openFile(argv[1]))
    if (netlist.openFile(file))
    {
        netlist.readFile();
        numberGates = netlist.getGatesCounter();
        
        netlist.adjMatrix.resize(numberGates);
        for (int i = 0; i < numberGates; i++)
            netlist.adjMatrix[i].resize(numberGates);
        
        for (int i = 0; i < numberGates; i++)
        {
            g = &(netlist.gates[i]);
            
            for (int j = 0; j < g->inputs.size(); j++)          // for each input
            {
                // check if the each input of the gate is an output of another gate
                int outin = netlist.find(&(netlist.outputs),g->inputs[j]);
                
                for (int k = 0; k < numberGates; k++)   // for each output
                {
                    g1 = &(netlist.gates[k]);
                    if (g1->output == netlist.outputs[outin])
                        netlist.adjMatrix[i][k] = 1;
                }
            }
            
            // check if gate output is input to other gates
        }
        
        cout << "file open" << endl;
        
        cout << "number of gates: " << numberGates << endl;
        
        for (int i = 0 ; i < numberGates; i++)
        {
            cout << netlist.gates[i].name << "  ";
            for (int j = 0; j < numberGates; j++)
                cout <<  netlist.adjMatrix[i][j];
            cout << endl;
        }
        
        /* TOPO SORT */
        TopoSort top(&netlist);
        top.KahnSort();
        
        cout << "main" << endl;
        
        for (int i = 0 ; i < top.sortedGates.size(); i++)
        {
            cout << top.sortedGates[i]  << endl;
        }
        
    }
    
    return 0;
}

