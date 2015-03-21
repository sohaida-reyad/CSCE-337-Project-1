//
//  DAG.h
//  DAG
//
//  Created by Mac on 3/20/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#ifndef DAG_h
#define DAG_h

#include <QString>
#include <fstream>
#include <QVector>
//#include <utility>
#include <QPair>

#include "gate.h"

using namespace std;

class DAG
{
public:
    
    DAG();
    ~DAG();
    
    bool openFile (const QString &);
    void readFile();
    qint64 getGatesCounter();
    qint64 find(QVector<QString>*, const QString &);
    
    QVector <gate> gates;
    QVector <QString> outputs;
    QVector <QString> inputs;
    QVector <QString> wires;
    
    QVector<QString> In;
    QVector<QString> Out;
    QVector<QString> InOut;
    QVector<QString> Wires;
    QVector<QPair<QString, QString> > Assign;

    QVector<QVector<qint64> > adjMatrix;
    
private:
    
    ifstream in;
    qint64 inCount;
    qint64 outCount;
    qint64 inoutCount;
    qint64 wiresCount;
    qint64 assignCount;
};

#endif
