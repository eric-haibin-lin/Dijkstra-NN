//
//  node.cpp
//  323Asst3Dijkstra
//
//  Created by Haibin Lin on 17/3/14.
//  Copyright (c) 2014 Haibin Lin. All rights reserved.
//

#include "node.h"
#include "edge.h"

Node :: Node(){
    return;
};


Node :: Node(int const & nodeId){
    this->nodeId = nodeId;
    distance = -1.0;
    visited = false;
    
    return;
};


void Node :: addEdge(Edge e){
    (this->adjacentEdge).push_back(e);
    return;
};

void Node:: deleteEdge(int edgeId){
    vector<Edge>::iterator it;
    for (it = this->adjacentEdge.begin(); it != this->adjacentEdge.end(); it ++){
        if (it -> getEdgeId() == edgeId){
            this->adjacentEdge.erase(it);
            return;
        }
    }

    cout << "Cannot find Edge " << edgeId << " in adjacency list!" << endl;
    return;

}


void Node:: setDist(double newDist){
    this->distance = newDist;
    return;
}

void Node:: setVisited(){
    this->visited = true;
}

int Node:: getId(){
    return this->nodeId;
}

double Node:: getDist(){
    return this->distance;
}

void Node:: printAdjacent(){
    vector<Edge>::iterator it;
    
    cout << "Node number " << this->nodeId << " adjacent list: ";
    for (it = this->adjacentEdge.begin(); it != this->adjacentEdge.end(); it++)
        cout << it->getLeftNodeId() << "-" << it->getRightNodeId() <<" ";
    cout <<endl;
    return;
}

vector<Edge> Node:: getAdjacent(){
    return  this->adjacentEdge;
}




