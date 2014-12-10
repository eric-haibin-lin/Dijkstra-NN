//
//  node.h
//  323Asst3Dijkstra
//
//  Created by Haibin Lin on 17/3/14.
//  Copyright (c) 2014 Haibin Lin. All rights reserved.
//

#ifndef ___23Asst3Dijkstra__node__
#define ___23Asst3Dijkstra__node__

#include <iostream>
#include <vector>

class Edge;

using namespace std;

class Node {
private:
    int nodeId;
    vector < Edge > adjacentEdge;
    
public:
    double distance;
    bool visited;
    
    Node();
    Node(int const & nodeId);
    
    void addEdge(Edge);
    void deleteEdge(int);
    
    void setDist(double);
    void setVisited();
    
    int getId();
    double getDist();
    vector<Edge> getAdjacent();
    
    void printAdjacent();
    
};






#endif /* defined(___23Asst3Dijkstra__node__) */
