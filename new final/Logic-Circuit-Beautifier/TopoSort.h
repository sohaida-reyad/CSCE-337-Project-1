//
//  TopoSort.h
//  TopoSort
//
//  Created by Mac on 3/21/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#ifndef TopoSort_H
#define TopoSort_H

#include <QString>
#include <QVector>
#include <QQueue>

#include "DAG.h"
#include "gate.h"

using namespace std;

class TopoSort
{
public:
    
    TopoSort(DAG*);                                 // constructor of DAG
    ~TopoSort();                                    // destructor
    
    void KahnSort();                                // performs Kahn sort
    
    QVector <QString> sortedGates;                  // resulting list of sorted gates
    QQueue <qint64> noEdgesIndex;                   // index of gates that are not connected to other gates

    void sortGates (DAG*);                          // fills sortedGates
    
private:
    
    //QVector< QVector < qint64> > AdjMatrix;         // adjacency matrix
    QQueue <gate> noIncomingEdges;                  // list of gates that are not connected to other gates
    //QQueue <qint64> noEdgesIndex;
    QVector<qint64> connectedGates;                 // list of gates connected to a certain gate

    DAG* dagPtr;                                    // pointer to DAG which will be sorted
    qint64 gatesCount;                              // number of gates
    qint64 levelCount;                              // counter for levels
    
    bool hasIncomingEdges(const qint64&);           // returns true if gate is connected to another gate
    void getConnectedGates(const qint64&);          // retrieves list of gates connected to the gate indicated by qint64
    qint16 find(QString&, QVector<gate>&);          // finds string in vector of strings (used for different uses)

    
};

#endif
