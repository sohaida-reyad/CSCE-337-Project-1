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
    
    TopoSort(DAG*);
    ~TopoSort();
    
    void KahnSort();
    
    QVector <QString> sortedGates;
    QQueue <qint64> noEdgesIndex;

    void sortGates (DAG*);
    
private:
    
    QVector< QVector < qint64> > AdjMatrix;
    QQueue <gate> noIncomingEdges;
    //QQueue <qint64> noEdgesIndex;
    QVector<qint64> connectedGates;
    
    DAG* dagPtr;
    qint64 gatesCount;
    qint64 levelCount;
    
    bool hasIncomingEdges(const qint64&);
    void getConnectedGates(const qint64&);
    qint16 find(QString&, QVector<gate>&);

    
};

#endif
