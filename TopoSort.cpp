//
//  main.cpp
//  TopSort
//
//  Created by Mac on 3/12/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>

using namespace std;

//bool TopoSort (vector<list<int> > &, vector<int> &);
bool TopoSort (vector<vector<int> > &, vector<int> &);
bool CheckEdges(const vector<int> &);

int main(int argc, const char * argv[]) {
    
    /* Declarations */
    ifstream in;
    ofstream out;
    
    //int AdjMatrix[1000][1000];                   //adjacency matrix
    //vector<list<int> > AdjList;                 // adjacency list/matrix
    vector<vector<int> > AdjList;                // adjacency list/matrix
    
    vector<int> aux;                             // auxilary vector used for filling 2D vector
    
    vector<int> Indegree;                        // has in-degrees of vertices; 0 means that the vertix
    // has no incoming nodes
    
    vector<int> SortedList;                      // used to store the sorted elements; primarily empty
    
    vector<int> ZeroIndegree;                    // used to save those vertices that have no incoming edges
    
    //int SortedList[1000];                          // sorted list
    
    char c;                                         // char obtained from file
    
    /* Parse file that contains the adjacency matrix */
    in.open(argv[1]);
    
    if (in.fail())
        cout << "Error opening file. " << endl;
    
    else
    {
        /* Parse file to get adjacency matrix */
        
        // get a number to represent the edge/connection between two nodes
        // this number is got as a character
        in.get(c);
        
        while (!in.eof())
        {
            // if the data for the first node has been all read (i.e. one line/row is read)
            // push data to the vector then clear auxilary vector
            if (c ==  '\n')
            {
                AdjList.push_back(aux);
                aux.clear();
            }
            
            else
            {
                // if there is still more data in the line/row (i.e. the char was data not newline)
                // convet this data (char) to int (i.e. converting character 0 to int 0)
                int k = int (c) - 48;
                
                // then push this data to the auxilary vector which will then be pushed to the AdjList
                aux.push_back(k);
            }
            
            in.get(c);
        }
    }
    
    /* Fill Indgree Vector */
    // get the number of connections/edges for each node in the graph
    // those connections are called in-degree (no. of edges coming into each node)
    for (int i = 0; i < AdjList.size(); i++)
    {
        // initially set the indegree to 0
        Indegree[i] = 0;
        
        // then check its connections with the other nodes
        for (int j = 0; j < AdjList.size(); i++)
        {
            // if the node has connections with nodes other than itself
            if (AdjList[i][j] != 0 && i != j)
                // update in-degree counter for that node index
                Indegree[i] ++;
        }
    }
    
    /* Apply Topological Sort and check success of process */
    if (TopoSort(AdjList,Indegree))
        cout << "Topological Sorting done sucessfully." << endl;
    else
        cout << "Topological Sorting failed." << endl;
    
    return 0;
}

bool TopoSort (vector<list<int> > & AdjList,
               vector<int> & Indegree
               )
{
    // this function performs Topological Sorting according to Kahn's Algorithm
    
    queue <int> ZeroIndegree;                       //tsort_queue // s
    vector<int> SortedList;                         // sorted // l
    
    int node;
    
    list<int>::iterator iterator;
    
    // get the nodes with zero in-degree (i.e. those with no incoming edges)
    for (int i = 0; i < Indegree.size(); i++)
    {
        if (Indegree[i]==0)
            ZeroIndegree.push(i);
    }
    
    while (!ZeroIndegree.empty()) {
        
        // remove a node from the queue of nodes that have no incoming edges
        node = ZeroIndegree.front();
        ZeroIndegree.pop();
        
        // append it to the list of sorted nodes
        SortedList.push_back(node);
        
        // for each node 'x' connected to 'node' through edge 'e'
        for (iterator = AdjList[node].begin(); iterator!= AdjList[node].end(); iterator++)
        {
            // remove the edge e from graph by decrementing the in-degree
            Indegree[*iterator] = Indegree[*iterator] -1;
            
            // if x has no incoming edges (i.e. has indegree = 0 )
            if (Indegree[*iterator] == 0)
                // append x to the queue of ZeroIndegree so that it gets processed
                ZeroIndegree.push(*iterator);
        }
    }
    
    if (CheckEdges(Indegree))
        return 1;
    else
        return 0;
}

bool CheckEdges(const vector<int> & Indegree)
{
    // traverse the Indegree to check that no edges exist
    for (int i = 0; i < Indegree.size(); i++)
    {
        // an edge means that the indegree > 0 (therefore, indegree == 0, it means that there are no edges)
        // if indegree == -1, it means that the node is not in the graph
        
        if (Indegree[i] > 0 && Indegree[i] != -1)
            return 0;
        // returning false means that there is an error, either that there is an node not in the graph
        // or that the graph still has edges
    }
    
    // if there are no edges and no nodes out of the graph, return true
    return 1;
}
