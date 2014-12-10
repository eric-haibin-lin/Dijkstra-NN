//
//  main.cpp
//  323Asst3Dijkstra
//
//  Created by Haibin Lin on 17/3/14.
//  Copyright (c) 2014 Haibin Lin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

#include "edge.h"
#include "node.h"

using namespace std;


void updateHeap(int currentNodeId);
void updateNodes(Edge & newEdge, int nodeId);
Node* searchNodeInList(int nodeId);
bool compare (Node * i,Node * j);
int splitEdge(int, int, double);
void printAdjacencyList();
void printDistanceQueue();
void printEdgeList();
void printPath(int nodeId);

vector<Edge> edgeList;
map<int, Node> nodeMap;
vector<Node* > nodeListWithDistance;

//Create a data struct for path!
map<int, vector <int> > pathMap;

int main(int argc, const char * argv[])
{
    ifstream inputFile;
    double edgeWeight;
    int edgeId, leftNodeId, rightNodeId;
    
    inputFile.open ("spatial_network.txt");
    
    while (inputFile >> edgeId >> leftNodeId >> rightNodeId >> edgeWeight){
        Edge newEdge(edgeId, leftNodeId, rightNodeId, edgeWeight);
        edgeList.push_back(newEdge);
        
        updateNodes(newEdge, leftNodeId);
        updateNodes(newEdge, rightNodeId);
    };
    
    
    //read in query node
    int leftNodeId1, rightNodeId1, leftNodeId2, rightNodeId2;
    double dist1, dist2;
    
    cout << "Please input the information of start node: " <<endl;
    cin >> leftNodeId1 >> rightNodeId1 >> dist1;
    cout << "Please input the information of destination node: " <<endl;
    cin >> leftNodeId2 >> rightNodeId2 >> dist2;
    
    /*
    
    leftNodeId1 = 0;
    rightNodeId1 = 1;
    dist1 = 1.0;
    
    leftNodeId2 = 5;
    rightNodeId2 =99;
    dist2 = 5.0;
     */
    
    //If the two nodes are on the same edge.
    if (leftNodeId1 == leftNodeId2 && rightNodeId1 == rightNodeId2){
        double dist =(dist1 > dist2) ? dist1 - dist2 : dist2 - dist1;
        cout << dist << endl;
        return 1;
    }
    
    int startId = splitEdge(leftNodeId1, rightNodeId1, dist1);
    int endId = splitEdge(leftNodeId2, rightNodeId2, dist2);
    
    //printAdjacencyList();
    //cout << "The start node id is " << startId << " ,the end node id is " << endId << endl;
    
    
    if (nodeMap.count(startId) == 0){
        cout << "Error: Encountered unknown node ..." <<endl;
        exit(-1);
    }
    
    //Initialize the distance heap.
    Node *newNode = & nodeMap[startId];
    newNode->setDist(0.0);
    nodeListWithDistance.push_back(newNode);
    
    while (1){
        //Pop out the nearest node
        int currentNodeId = nodeListWithDistance[0]->getId();
        //cout << "Pop current node " << currentNodeId << " with dist: " << nodeListWithDistance[0]->getDist() << endl;
        
        if (currentNodeId == endId){
            
            cout << nodeListWithDistance[0]->getDist() << endl;
            
            nodeListWithDistance.erase(nodeListWithDistance.begin());
            updateHeap(currentNodeId);
            printPath(endId);
            
            break;
        }
        
        nodeListWithDistance.erase(nodeListWithDistance.begin());
        
        //Update the heap with these adjacent node
        updateHeap(currentNodeId);
        //printDistanceQueue();
    }
    
    //printEdgeList();
    //printDistanceQueue();
    inputFile.close();
    return 0;
}

void updateNodes(Edge & newEdge, int nodeId){
    if (nodeMap.count(nodeId) == 0){
        Node newNode = Node(nodeId);
        nodeMap[nodeId] = newNode;
    }
    
    Node * newNode = & nodeMap[nodeId];
    newNode->addEdge(newEdge);
    return;
}

int splitEdge(int leftNodeId, int rightNodeId, double dist){
    vector<Edge>::iterator it;
    int newNodeId;
    
    
    if (dist < 0){
        cout << "The input distance cannot be negative. " <<endl;
        exit(-1);
    }
    
    for (it = edgeList.begin(); it != edgeList.end(); it++){
        //Find the edge to split.
        if (it->getLeftNodeId() == leftNodeId && it->getRightNodeId() == rightNodeId){
            if (dist == 0)
                return leftNodeId;
            if (dist == it->getEdgeWeight())
                return rightNodeId;
            
            if (dist > it->getEdgeWeight()){
                cout << "The distance input is larger than expected. " << endl;
                exit(-1);
            }
            
            //Deal with the case where the newNode is in the middle of an edge.
            int edgeIdLeft, edgeIdRight;
            newNodeId = (int) nodeMap.size() + 1;
            edgeIdLeft = (int) edgeList.size() + 1;
            edgeIdRight = edgeIdLeft + 1;
            
            //Create new node and edges.
            Node newNode = Node(newNodeId);
            Edge newEdgeLeft(edgeIdLeft, leftNodeId, newNodeId, dist);
            edgeList.push_back(newEdgeLeft);
            Edge newEdgeRight(edgeIdRight, rightNodeId, newNodeId, it->getEdgeWeight() - dist);
            edgeList.push_back(newEdgeRight);
            
            newNode.addEdge(newEdgeRight);
            newNode.addEdge(newEdgeLeft);
            
            nodeMap[newNodeId] = newNode;
            
            //Modify the node related to Old left Node & Old right Node;
            Node * oldLeftNode = & nodeMap[leftNodeId];
            Node * oldRightNode = & nodeMap[rightNodeId];
            
            oldLeftNode->deleteEdge(it->getEdgeId());
            oldLeftNode->addEdge(newEdgeLeft);
            
            oldRightNode->deleteEdge(it->getEdgeId());
            oldRightNode->addEdge(newEdgeRight);
            return newNodeId;
        }
        
    }
    
    cout << "Cannot find the edge to split." << endl;
    exit(-1);
}


void updateHeap(int currentNodeId){
    vector<Edge> adjacentEdgeList;
    Node* currentNode = & nodeMap[currentNodeId];
    
    adjacentEdgeList = currentNode->getAdjacent();
    currentNode->setVisited();
    
    vector<Edge>::iterator adjacentIt;
    for (adjacentIt = adjacentEdgeList.begin(); adjacentIt != adjacentEdgeList.end(); adjacentIt++){
        //Get the other end of the edge
        int adjacentNodeId = (adjacentIt->getLeftNodeId() == currentNodeId) ? adjacentIt->getRightNodeId() : adjacentIt->getLeftNodeId();
        
        Node* newNode = & nodeMap[adjacentNodeId];
        
        double newWeight = adjacentIt->getEdgeWeight();
        //cout <<newWeight <<endl;
        //cout << currentNode->getDist() <<endl;
        
        //If this adjacent node is a node not yet visited.
        if (newNode->visited == false){
            newNode = searchNodeInList(adjacentNodeId);
            //if the node distance is not calculated yet.
            if (newNode == NULL){
                newNode = & nodeMap[adjacentNodeId];
                newNode->setDist(currentNode->getDist() + newWeight );
                nodeListWithDistance.push_back(newNode);
                vector<int> newPath = pathMap[currentNodeId];
                newPath.push_back(newNode->getId());
                pathMap[newNode->getId()] = newPath;
                //cout << "add new node " << newNode->getId() << " with dist " << newNode->getDist() << " to the list. "<<endl;
            }

            else
                //It's an old node. compare if current distance is shorter
                if (newNode->getDist() > (currentNode->getDist() + newWeight)){
                    newNode->setDist(currentNode->getDist() + newWeight);
                    vector<int> newPath = pathMap[currentNodeId];
                    newPath.push_back(newNode->getId());
                    pathMap[newNode->getId()] = newPath;
                    
                    //cout << "update old node " << newNode->getId() << " with dist " << newNode->getDist() << " to the list. "<<endl;
                }
                //else cout << "old node " << newNode->getId() << " with dist " << newNode->getDist() << " is not updated."<<endl;
        }
        //else cout << newNode->getId() << " node already Visited!" <<endl;
    }
    sort(nodeListWithDistance.begin(), nodeListWithDistance.end(), compare);
    
    return;
};


Node* searchNodeInList(int nodeId){
    Node* targetNode = NULL;
    
    vector<Node*>::iterator it;
    for (it = nodeListWithDistance.begin(); it != nodeListWithDistance.end(); it ++){
        if ( (*it)->getId() == nodeId){
            targetNode = (*it);
            break;
        }
    }
    return targetNode;
}

bool compare (Node * i,Node * j) { return (i->getDist()<j->getDist()); }


//Print the adjacency list
void printAdjacencyList(){
    map<int, Node>::iterator mapIt;
    for (mapIt = nodeMap.begin(); mapIt != nodeMap.end(); mapIt ++){
        mapIt->second.printAdjacent();
    }
};

//Print node distance queue.
void printDistanceQueue(){
    vector<Node*>::iterator nodeDistIt;
    for (nodeDistIt = nodeListWithDistance.begin(); nodeDistIt != nodeListWithDistance.end(); nodeDistIt ++){
        cout << "node "<< (*nodeDistIt)->getId() << " with dist " << (*nodeDistIt)->getDist() << endl;
    }
};

void printEdgeList(){
    vector<Edge>::iterator it;
    for (it = edgeList.begin(); it != edgeList.end(); it ++){
        cout << (*it).getEdgeId() << endl;
    }
};


void printPath(int nodeId){
    vector<int>::iterator it;
    
    if (pathMap[nodeId].size() == 0 )
        return;
    else
        for (it = pathMap[nodeId].begin(); it != (pathMap[nodeId].end()) ; it ++){
            if ((*it) == nodeId )
                break;
            cout << (*it) <<" " ;
        }
    cout << endl;
};
