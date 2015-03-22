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
#include <QPair>
#include <QTextStream>
#include <QFile>

#include "gate.h"

using namespace std;

class DAG
{
public:
    
    DAG();                                                  // constructor
    ~DAG();                                                 // destructor
    
    bool readFile(const QString &);                         // opens and reads file to create graph
    qint64 getGatesCounter();                               // returns count of number of gates
    qint64 find(QVector<QString>*, const QString &);        // searches for string in vector (used in many cases)
    
    QVector <gate> gates;                                   // vector of gates (please see gate.h)
    QVector <QString> outputs;                              // list of outputs from each gate instance
    QVector <QString> inputs;                               // list of inputs from each gate instance
    QVector <QString> wires;                                // list of outputs from each gate instance
    
    QVector<QString> In;                                    // list of inputs from begining of file
    QVector<QString> Out;                                   // list of outputs from begining of file
    QVector<QString> InOut;                                 // list of inout ports from begining of file
    QVector<QString> Wires;                                 // list of wires from begining of file
    QVector<QPair<QString, QString> > Assign;               // list of assigns from begining of file (2 params)

    QVector<QVector<qint64> > adjMatrix;                    // resulting adjacency matrix
    
private:

    qint64 inCount;                                         // inputs count
    qint64 outCount;                                        // outputs count
    qint64 inoutCount;                                      // inout count
    qint64 wiresCount;                                      // wire count
    qint64 assignCount;                                     // assign count
};

#endif
