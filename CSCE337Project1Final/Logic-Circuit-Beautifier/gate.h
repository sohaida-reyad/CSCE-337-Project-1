//
//  gate.h
//  Logic Circuit Schematic Beautifier
//
//  Created by Mac on 3/21/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#ifndef gate_h
#define gate_h

#include <QString>
#include <QVector>

using namespace std;

class gate
{
    // gate class that saves all gate attributes
public:
    QString name;                                       // name of gate
    qint64 num_inputs;                                  // number of inputs
    QVector <QString> inputs;                           // list of inputs names
    QString output;                                     // output name
    qint64 level;                                       // level number
};

#endif
