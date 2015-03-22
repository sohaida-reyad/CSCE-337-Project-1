//
//  DAG.cpp
//  DAG
//
//  Created by Mac on 3/20/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#include <fstream>
#include <QString>
//#include <iostream>
//#include <stdlib.h>
#include <QFile>

#include "DAG.h"
#include "gate.h"

using namespace std;

DAG :: DAG()
{
}

DAG ::~DAG()
{
}

/*
bool DAG ::openFile(const QString& fileName)
{
    file(fileName);

    if(file.open(QFile::ReadOnly))
    //in.open(fileName);
    
    //if (in.fail())
        return 0;
    else
        return 1;
}
*/

bool DAG ::readFile(const QString& fileName)
{


    gate * g = new gate;
    QString s, s1, numInputs, gateName, gateNumber;
    
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly))
    //in.open(fileName);

    //if (in.fail())
        return 0;
    else
        //return 1;
    {
         QTextStream in(&file);
    // inputs
    in >> s ;
    inCount = s.toInt();
    for (qint16 i = 0; i < inCount; i++)
    {
        in >> s >> s1;
        In.push_back(s+s1);
    }
    
    // outputs
    in >> s ;
    outCount = s.toInt();
    for (qint16 i = 0; i < outCount; i++)
    {
        in >> s >> s1;
        Out.push_back(s+s1);
    }
    
    // inout
    in >> s ;
    inoutCount = s.toInt();
    for (qint16 i = 0; i < inoutCount; i++)
    {
        in >> s >> s1;
        InOut.push_back(s+s1);
    }
    
    // wires
    in >> s ;
    wiresCount = s.toInt();
    for (qint16 i = 0; i < wiresCount; i++)
    {
        in >> s;
        Wires.push_back(s);
    }
    
    // assign
    in >> s ;
    assignCount = s.toInt();
    for (qint16 i = 0; i < assignCount; i++)
    {
        in >> s >> s1;
        QPair<QString, QString> p (s, s1);
        Assign.push_back(p);
    }
    
    // gates
    in >> gateName;
    while (!in.atEnd()) {
        
        in >> gateNumber;
        g->name = gateName + gateNumber;
        
        in >> numInputs;
        g->num_inputs = numInputs.toInt();
      
        for (qint16 i = 0 ; i < g->num_inputs; i++)
        {
            in >> s;
            g->inputs.push_back(s);
            
            if (find(&inputs, s) == -1)
                inputs.push_back(s);
        }
        
        in >> g->output;
        if (find(&outputs, g->output) == -1)
            outputs.push_back(g->output);
        
        gates.push_back(*g);
        
        g->inputs.clear();
        
        in >> gateName; 
    }
    
    delete g;
    
    file.close();
    return 1;
    }
}

qint64 DAG :: getGatesCounter()
{
    return (gates.size()); 
}

qint64 DAG :: find(QVector<QString>* vec, const QString & st)
{
    for (qint16 i=0; i< vec->size(); i++)
        if ( vec->at(i)== st)
            return i;
    
    return -1;      // not found
}

