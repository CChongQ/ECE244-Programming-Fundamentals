/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include "Node.h"

using namespace std;

Node::Node(){}
Node::~Node(){}
Node::Node(int value,ResistorList* newRes){
    nodeID = value;
    Nnext=NULL;
    headR = newRes;
    
}
Node::Node(int value, Node* newNode) {
    nodeID = value;
    Nnext = newNode;   
}

Node* Node::getNext() {
    return(Nnext);
}

void Node::setVoltage(double value){
    
    voltage = value;
    
}
double Node::getVoltage(){
    
    return voltage;
}
int Node::getID(){
    return nodeID;
}
void Node::setNext( Node* newNode){
    
    Nnext = newNode;
    
}
void Node::setResHead(ResistorList* newHead){
    headR = newHead;
}
ResistorList* Node::getResHead(){
    return(headR);
    
}

bool Node::checkV(){
    return (setV);
    
}
void Node::checkSet(){
    setV = true;
}

void Node::unsetVC(){
    setV=false;
}

void Node::printN(){
    
    // print information of a node
    int countRes=0; // how many resistors are connect to this node
    Resistor* temp = headR->getRH();
    
    while(temp != NULL){
        countRes++;
        temp = temp->getNext();
    }   
    if (countRes !=0) {
        cout<< "Connections at node " << nodeID << ": " << countRes << " resistor(s)"<<endl;
        Resistor* printN = headR->getRH();
        while (printN!=NULL){
           printN->printR();
           printN = printN->getNext();
        }
    }
}