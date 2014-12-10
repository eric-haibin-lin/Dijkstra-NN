//
//  edge.cpp
//  323Asst3Dijkstra
//
//  Created by Haibin Lin on 17/3/14.
//  Copyright (c) 2014 Haibin Lin. All rights reserved.
//

#include "edge.h"
#include "node.h"
using namespace std;

Edge :: Edge(int edgeId, int leftNodeId,int rightNodeId, double edgeWeight){
    this->edgeId = edgeId;
    this->leftNodeId = leftNodeId;
    this->rightNodeId = rightNodeId;
    this->edgeWeight = edgeWeight;
    return;
};

int Edge:: getEdgeId(){
    return this->edgeId;
}

int Edge :: getLeftNodeId(){
    return this->leftNodeId;
};

int Edge :: getRightNodeId(){
    return this->rightNodeId;
};

double Edge :: getEdgeWeight(){
    return this->edgeWeight;
};


