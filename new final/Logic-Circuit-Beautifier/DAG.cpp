//
//  DAG.cpp
//  DAG
//
//  Created by Mac on 3/20/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#include <fstream>
#include <QString>
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

bool DAG ::readFile(const QString& fileName)
{
    gate * g = new gate;
    QString s, s1, numInputs, gateName, gateNumber;
    
    QFile file(fileName);                                   // opens file

    if(!file.open(QFile::ReadOnly))                         // checks that file is open
        return 0;                                           // if failed to open, return false
    else
    {
         QTextStream in(&file);                              // create stream

         // inputs
         in >> s ;
         inCount = s.toInt();                                 // retrieve count and inputs
         for (qint16 i = 0; i < inCount; i++)
         {
             in >> s >> s1;
             In.push_back(s+s1);
         }

         // outputs
         in >> s ;
         outCount = s.toInt();                                // retrieve count and outputs
         for (qint16 i = 0; i < outCount; i++)
         {
             in >> s >> s1;
             Out.push_back(s+s1);
         }

         // inout
         in >> s ;
         inoutCount = s.toInt();                            // retrieve count and inout
         for (qint16 i = 0; i < inoutCount; i++)
         {
             in >> s >> s1;
             InOut.push_back(s+s1);
         }

         // wires
         in >> s ;
         wiresCount = s.toInt();                            // retrieve count and wires
         for (qint16 i = 0; i < wiresCount; i++)
         {
             in >> s;
             Wires.push_back(s);
         }

         // assign
         in >> s ;
         assignCount = s.toInt();                           // retrieve count and assigns
         for (qint16 i = 0; i < assignCount; i++)
         {
             in >> s >> s1;
             QPair<QString, QString> p (s, s1);
             Assign.push_back(p);
         }

         // gates
         in >> gateName;                                    // retrieves gate name
         while (!in.atEnd()) {

             in >> gateNumber;                              // retrieves gate number
             g->name = gateName + gateNumber;               // saves the concatenated in gate

             in >> numInputs;                               // retrieves number of inputs
             g->num_inputs = numInputs.toInt();             // saves them in gate

             for (qint16 i = 0 ; i < g->num_inputs; i++)    // puts inputs in corresponding vector
             {
                 in >> s;
                 g->inputs.push_back(s);

                 if (find(&inputs, s) == -1)
                     inputs.push_back(s);
             }

             in >> g->output;                               // retrieves number of inputs
             if (find(&outputs, g->output) == -1)
                 outputs.push_back(g->output);

             gates.push_back(*g);                           // pushes gate in vector of gates

             g->inputs.clear();                             // clears it in preparation for next iteration

             in >> gateName;                                // gets next gate's name
         }

    delete g;                                               // deletes what g points at
    
    file.close();                                           // closes file
    return 1;
    }
}

qint64 DAG :: getGatesCounter()
{
    return (gates.size());                                  // returns size of number of gates
}

qint64 DAG :: find(QVector<QString>* vec, const QString & st)
{
    // searches for st in vec and returns its index if found (-1 otherwise)

    for (qint16 i=0; i< vec->size(); i++)
        if ( vec->at(i)== st)
            return i;
    
    return -1;      // not found
}

