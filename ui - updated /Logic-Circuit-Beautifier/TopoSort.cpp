//
//  TopoSort.cpp
//  TopoSort
//
//  Created by Mac on 3/21/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#include "TopoSort.h"
#include "DAG.h"
#include "gate.h"
#include <iostream>

using namespace std;

TopoSort::TopoSort(DAG* dag)
{
    dagPtr = dag;
    levelCount = 1;
    
    vector <gate> v;
    
    // set level of all gates to 1 (0 is for inputs)
    
    // fill noincomingedges
    gatesCount = dagPtr->getGatesCounter();
    
    for (int i = 0; i < gatesCount; i++)
    {
        if (!hasIncomingEdges(i)){
            noIncomingEdges.push(dagPtr->gates[i]);
            v.push_back(dagPtr->gates[i]);
            noEdgesIndex.push(i);
            dagPtr->gates[i].level = 1;
        }
    }
    /*
    cout << "const" << endl;
    
    for (int i = 0 ; i <v.size(); i++)
    {
        cout << v[i].name << endl;
    }
    
 */
}

TopoSort::~TopoSort()
{
}

void TopoSort::KahnSort()
{
    // follow wiki
    gate g;
    int j ;
    
    //cout << "enter kahn sort" << endl;
    
    while (!noIncomingEdges.empty()) {
        
        g = noIncomingEdges.front();
        j = noEdgesIndex.front();
        
        noIncomingEdges.pop();
        noEdgesIndex.pop();
        
        sortedGates.push_back(g.name);
        //dagPtr->gates[j].level = levelCount;

        // get nodes connected to gate g (using col find rows)
        
        getConnectedGates(j);
        
        for (int i = 0; i < connectedGates.size(); i++) {
            dagPtr->adjMatrix[connectedGates[i]][j] = 0;
            if (!hasIncomingEdges(connectedGates[i])){
                noIncomingEdges.push(dagPtr->gates[connectedGates[i]]);
                noEdgesIndex.push(connectedGates[i]);
                
                dagPtr->gates[connectedGates[i]].level = dagPtr->gates[j].level + 1;
                
                cout <<  dagPtr->gates[connectedGates[i]].level << endl;
                
            }
        }
        
       
    }
    
}

bool TopoSort::hasIncomingEdges(const int & i)
{
    for (int j = 0; j < gatesCount; j++)
    {
        if (dagPtr->adjMatrix[i][j] == 1) {
            return 1;
        }
    }
    return 0;
}

void TopoSort::getConnectedGates(const int & j)
{
    connectedGates.clear();
    
    for (int i = 0; i < gatesCount; i++)
    {
        if (dagPtr->adjMatrix[i][j] == 1)
            connectedGates.push_back(i); 
    }
}
