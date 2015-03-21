//
//  gate.h
//  Logic Circuit Schematic Beautifier
//
//  Created by Mac on 3/21/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#ifndef gate_h
#define gate_h

#include <string>
#include <vector>

using namespace std;

class gate
{
public:
    string name;
    int num_inputs;
    vector <string> inputs;
    string output;
    int level;
};

#endif
