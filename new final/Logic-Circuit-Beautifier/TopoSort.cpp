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
    
    QVector <gate> v;
    
    // set level of all gates to 1 (0 is for inputs)
    
    // fill noincomingedges
    gatesCount = dagPtr->getGatesCounter();
    
    for (qint64 i = 0; i < gatesCount; i++)
    {
        if (!hasIncomingEdges(i)){
            noIncomingEdges.enqueue(dagPtr->gates[i]);
            v.push_back(dagPtr->gates[i]);
            noEdgesIndex.enqueue(i);
            dagPtr->gates[i].level = 1;
        }
    }

}

TopoSort::~TopoSort()
{
}

void TopoSort::KahnSort()
{
    // follow wiki
    gate g;
    qint64 j  ;
    
    //cout << "enter kahn sort" << endl;
    
    while (!noIncomingEdges.empty()) {
        
        g = noIncomingEdges.front();
        j = noEdgesIndex.front();
        
        noIncomingEdges.dequeue();
        noEdgesIndex.dequeue();
        
        sortedGates.push_back(g.name);
        //dagPtr->gates[j].level = levelCount;

        // get nodes connected to gate g (using col find rows)
        
        getConnectedGates(j);
        
        for (qint64 i = 0; i < connectedGates.size(); i++) {
            dagPtr->adjMatrix[connectedGates[i]][j] = 0;
            if (!hasIncomingEdges(connectedGates[i])){
                noIncomingEdges.enqueue(dagPtr->gates[connectedGates[i]]);
                noEdgesIndex.enqueue(connectedGates[i]);
                
                dagPtr->gates[connectedGates[i]].level = dagPtr->gates[j].level + 1;
                
                cout <<  dagPtr->gates[connectedGates[i]].level << endl;
                
            }
        }
        
       
    }
    
}

bool TopoSort::hasIncomingEdges(const qint64& i)
{
    for (qint64 j = 0; j < gatesCount; j++)
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
    
    for (qint64 i = 0; i < gatesCount; i++)
    {
        if (dagPtr->adjMatrix[i][j] == 1)
            connectedGates.push_back(i); 
    }
}

void TopoSort:: sortGates (DAG* dag)
{
    //DAG* dPtr = dag;
    gate g;

    for (qint16 i = 0; i< gatesCount; i++)
    {
        // find sorted gate [i] in DAG gates
        qint16 index = find(sortedGates[i], dagPtr->gates);

        if (index!=-1)
        {
            g = dagPtr->gates[index];
            dag->gates.push_back(g);
        }
    }

}

qint16 TopoSort:: find(QString& g, QVector <gate> & gates)
{
    for ( qint16 i = 0; i < gates.size(); i++)
        if (gates[i].name == g)
            return i;

    return -1;
}
