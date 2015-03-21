//
//  DAG.h
//  DAG
//
//  Created by Mac on 3/20/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#ifndef DAG_h
#define DAG_h

#include <string>
#include <fstream>
#include <vector>

#include "gate.h"

using namespace std;

class DAG
{
public:
    
    /*
    class gate
    {
    public:
        string name;
        int num_inputs;
        vector <string> inputs;
        string output;
        int level; 
    };
    */
    
    DAG();
    ~DAG();
    
    bool openFile (const string &);
    void readFile();
    unsigned int getGatesCounter();
    int find(vector<string>*, const string &);
    
    vector <gate> gates;
    vector <string> outputs;
    vector <string> inputs;
    vector <string> wires;
    
    vector<vector<int> > adjMatrix;
    
private:
    
    ifstream in;
};

#endif
