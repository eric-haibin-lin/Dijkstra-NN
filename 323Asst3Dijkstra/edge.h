//
//  edge.h
//  323Asst3Dijkstra
//
//  Created by Haibin Lin on 17/3/14.
//  Copyright (c) 2014 Haibin Lin. All rights reserved.
//

#ifndef ___23Asst3Dijkstra__edge__
#define ___23Asst3Dijkstra__edge__

#include <iostream>
#include "node.h"

using namespace std;

class Edge {
private:
    int edgeId, leftNodeId, rightNodeId;
    double edgeWeight;
    
public:
    Edge(int edgeId, int leftNodeId,int rightNodeId, double edgeWeight);
    
    int getEdgeId();
    int getLeftNodeId();
    int getRightNodeId();
    double getEdgeWeight();
    
};


#endif /* defined(___23Asst3Dijkstra__edge__) */
