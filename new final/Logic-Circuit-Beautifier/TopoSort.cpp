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
    // constructor

    dagPtr = dag;
    levelCount = 1;
    
    QVector <gate> v;
    
    // set level of all gates to 1 (0 is for inputs)
    
    // fill noincomingedges
    gatesCount = dagPtr->getGatesCounter();                         // retrieves counter of gates
    
    for (qint64 i = 0; i < gatesCount; i++)
    {
        if (!hasIncomingEdges(i)){                                  // if gate is not connected to another gate
            noIncomingEdges.enqueue(dagPtr->gates[i]);              // append it to queue
            v.push_back(dagPtr->gates[i]);                          // pushes gate to vector v
            noEdgesIndex.enqueue(i);                                // appends gate index in queue
            dagPtr->gates[i].level = 1;                             // sets its level to 1 (level after inputs)
        }
    }

}

TopoSort::~TopoSort()
{
}

void TopoSort::KahnSort()
{
    gate g;
    qint64 j  ;

    while (!noIncomingEdges.empty()) {                              // while the queue is not empty
        
        g = noIncomingEdges.front();                                // get the first gate
        j = noEdgesIndex.front();                                   // gets its index
        
        noIncomingEdges.dequeue();
        noEdgesIndex.dequeue();
        
        sortedGates.push_back(g.name);                              // pushes gate to the vector of sorted gates
        //dagPtr->gates[j].level = levelCount;

        // get nodes connected to gate g (using col find rows)
        
        getConnectedGates(j);                                       // gets list of gates that are connected to the current gate
        
        for (qint64 i = 0; i < connectedGates.size(); i++) {        // for each of these gates
            dagPtr->adjMatrix[connectedGates[i]][j] = 0;            // remove connection
            if (!hasIncomingEdges(connectedGates[i])){              // if it has noincoming connections
                noIncomingEdges.enqueue(dagPtr->gates[connectedGates[i]]);  // add it to the queue of no edges
                noEdgesIndex.enqueue(connectedGates[i]);              // add its index too
                
                dagPtr->gates[connectedGates[i]].level = dagPtr->gates[j].level + 1;    // make its level one more than the level that it was connected to
                
                cout <<  dagPtr->gates[connectedGates[i]].level << endl;
                
            }
        }
    }
}

bool TopoSort::hasIncomingEdges(const qint64& i)
{
    for (qint64 j = 0; j < gatesCount; j++)         // if gate i is connected to other gates behind it, return true
    {
        if (dagPtr->adjMatrix[i][j] == 1) {
            return 1;
        }
    }
    return 0;
}

void TopoSort::getConnectedGates(const qint64& j)
{
    connectedGates.clear();
    
    for (qint64 i = 0; i < gatesCount; i++)         // gets list of gates that are connected the the current gate j
    {
        if (dagPtr->adjMatrix[i][j] == 1)
            connectedGates.push_back(i); 
    }
}

void TopoSort:: sortGates (DAG* dag)                // sorts DAG according to the sortedGates
{
    gate g;

    for (qint16 i = 0; i< gatesCount; i++)
    {
        // find sorted gate [i] in DAG gates
        qint16 index = find(sortedGates[i], dagPtr->gates);

        if (index!=-1)
        {
            g = dagPtr->gates[index];
            dag->gates.push_back(g);                // if found, add it to the sorted list of gates
        }
    }

}

qint16 TopoSort:: find(QString& g, QVector <gate> & gates)
{
    // finds g in gates

    for ( qint16 i = 0; i < gates.size(); i++)
        if (gates[i].name == g)
            return i;

    return -1;
}
