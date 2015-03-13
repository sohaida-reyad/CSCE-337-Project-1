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

bool TopoSort ( vector<vector<int> > &, int, vector<int> &, vector<int> &);
bool CheckEdges(const vector<int> &);
void getEdges (const vector<vector<int> >, int, const vector<int> & );


int main(int argc, const char * argv[]) {
    
    /* Declarations */
    ifstream in;
    ofstream out;
    
    //int AdjMatrix[1000][1000];                   //adjacency matrix
    vector<vector<int> > AdjMatrix;                // adjacency list/matrix
    
    vector<int> aux;                             // auxilary vector used for filling 2D vector
    
    vector<int> Edge;                        // has in-degrees of vertices; 0 means that the vertix
    // has no incoming nodes
    
    vector<int> SortedList;                      // used to store the sorted elements; primarily empty
    
    //vector<int> ZeroEdge;                    // used to save those vertices that have no incoming edges
    
    //int SortedList[1000];                          // sorted list
    
    char c;                                         // char obtained from file
    int counter = 0;                                    // counter for number of nodes
    
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
                AdjMatrix.push_back(aux);
                
                // get count of nodes
                counter  = AdjMatrix.size();
                
                // clear vector for next iteration
                aux.clear();
            }
            
            else
            {
                // if there is still more data in the line/row (i.e. the char was data not newline)
                // convet this data (char) to int (i.e. converting character 0 to int 0)
                int k = int (c) - 48;
                
                // then push this data to the auxilary vector which will then be pushed to the AdjMatrix
                aux.push_back(k);
            }
            
            in.get(c);
        }
        
    }
    
    /* Fill Edges Vector */
    getEdges(AdjMatrix, counter, Edge);
    
    /* Apply Topological Sort and check success of process */
    if (TopoSort(AdjMatrix, counter, Edge, SortedList))
        cout << "Topological Sorting done sucessfully." << endl;
    else
        cout << "Topological Sorting failed." << endl;
    
    return 0;
}

bool TopoSort ( vector<vector<int> > & AdjMatrix,
               int counter,
               vector<int> & Edge,
               vector<int> & SortedList
               )
{
    // this function performs Topological Sorting according to Kahn's Algorithm
    
    queue <int> ZeroEdge;               // list of indeces of nodes that have no incoming edges
    
    int node;                               // index of node in graph
    
    // get the nodes with with no incoming edges
    for (int i = 0; i < Edge.size(); i++)
    {
        if (Edge[i]==0)
            ZeroEdge.push(i);
    }
    
    while (!ZeroEdge.empty()) {
        
        // remove a node from the queue of nodes that have no incoming edges
        node = ZeroEdge.front();
        ZeroEdge.pop();
        
        // append it to the list of sorted nodes
        SortedList.push_back(node);
        
        // for each node 'i' connected to 'node' through edge 'e' (i.e. AdjMatrix[i][node] == 1 )
        for (int i = 0; i < counter; i++)
        {
             if (i!= node && AdjMatrix[i][node] != 0) {
                 // remove the edge e from graph by decrementing the in-degree
                 AdjMatrix[i][node] = AdjMatrix[i][node] -1;
            
            // update Edge vector after the graph has been updated
            getEdges(AdjMatrix, counter, Edge);
                 
            // if i now has no incoming edges (i.e. has Edge = 0 )
            if (Edge[i] == 0)
                // append i to the queue of ZeroEdge so that it gets processed
                ZeroEdge.push(i);
        }
    }
    
    // At this point, if the adjacency list read from the file was DAG, it means that 'SortedList' will have the
    // topoligically sort of nodes
    
    // check if there are any other edges
    // if there are edges it means that it was cyclic
    if (CheckEdges(Edge))
        return 1;
    else
        return 0;
}
    
void getEdges (const vector<vector<int> > & AdjMatrix,
               int counter,
               const vector<int> & Edge)
{
    // get the number of connections/edges for each node in the graph
    // those connections are called in-degree (no. of edges coming into each node)
    for (int i = 0; i < counter; i++)
    {
        // initially set the Edge to 0
        Edge[i] = 0;
        
        // then check its connections with the other nodes
        for (int j = 0; j < counter; i++)
        {
            // if the node has connections with nodes other than itself
            if (AdjMatrix[i][j] != 0 && i != j)
                // update in-degree counter for that node index
                Edge[i] ++;
        }
    }
}
    
bool CheckEdges(const vector<int> & Edge)
{
    // traverse the Edge to check that no edges exist
    for (int i = 0; i < Edge.size(); i++)
    {
        // an edge means that the Edge > 0 (therefore, Edge == 0, it means that there are no edges)
        // if Edge == -1, it means that the node is not in the graph
        
        if (Edge[i] > 0 && Edge[i] != -1)
            return 0;
        // returning false means that there is an error, either that there is an node not in the graph
        // or that the graph still has edges
    }
    
    // if there are no edges and no nodes out of the graph, return true
    return 1;
}
