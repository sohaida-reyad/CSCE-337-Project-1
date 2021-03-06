//
//  DAG.cpp
//  DAG
//
//  Created by Mac on 3/20/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "DAG.h"
#include "gate.h"

using namespace std;

DAG :: DAG()
{
}

DAG ::~DAG()
{
}

bool DAG ::openFile(const string& fileName)
{
    in.open(fileName.c_str());
    
    if (in.fail())
        return 0;
    else
        return 1;
}

void DAG ::readFile()
{
    gate * g = new gate;
    string numInputs, s, gateName, gateNumber;
    
    in >> gateName;
    while (!in.eof()) {
        
        in >> gateNumber;
        g->name = gateName + gateNumber;
        
        in >> numInputs;
        g->num_inputs = atoi(numInputs.c_str());
      
        for (int i = 0 ; i < g->num_inputs; i++)
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
    
    in.close(); 
}

unsigned int DAG :: getGatesCounter()
{
    return (gates.size()); 
}

int DAG :: find(vector<string>* vec, const string & st)
{
    for (int i=0; i< vec->size(); i++)
        if ( vec->at(i)== st)
            return i;
    
    return -1;      // not found
}

