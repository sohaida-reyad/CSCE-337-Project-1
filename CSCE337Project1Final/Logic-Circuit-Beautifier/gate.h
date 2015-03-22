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
public:
    QString name;
    qint64 num_inputs;
    QVector <QString> inputs;
    QString output;
    qint64 level;
};

#endif
