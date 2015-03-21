//
//  TopoSort.h
//  TopoSort
//
//  Created by Mac on 3/21/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#ifndef TopoSort_H
#define TopoSort_H

#include <string>
#include <vector>
#include <queue>

#include "DAG.h"
#include "gate.h"

using namespace std;

class TopoSort
{
public:
    
    TopoSort(DAG*);
    ~TopoSort();
    
    void KahnSort();
    
    vector <string> sortedGates;
    
private:
    
    vector <vector<int> > AdjMatrix;
    queue  <gate> noIncomingEdges;
    queue  <int> noEdgesIndex; 
    vector <int> connectedGates;
    
    DAG* dagPtr;
    int gatesCount;
    int levelCount;
    
    bool hasIncomingEdges(const int &);
    void getConnectedGates(const int &); 
    
    
};

#endif