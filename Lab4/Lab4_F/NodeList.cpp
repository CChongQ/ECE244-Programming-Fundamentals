/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.cpp
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 7:41 PM
 */

#include <cstdlib>
#include <iomanip>
#include "NodeList.h"

using namespace std;



NodeList::~NodeList(){}
NodeList::NodeList(){
    head = NULL;   
}
NodeList::NodeList(Node* newHead){
    head=newHead;
}

Node* NodeList::getHead(){
    return head;
}
void NodeList::setHead(Node* newHead){
    
    head = newHead;
}

Node* NodeList::findNode(int newID,bool* where){
    //this function iterates through the node list to find a node with given nodeID
    Node* tptr = head;
    while (tptr != NULL) {
        if (tptr->getID() == newID ) {
            *where = true;
            return (tptr);
        }
        tptr = tptr->getNext();
    }
     *where = false;
         //node does not exist , find where to insert the node
         Node* temp = head;   
         Node* last = head;
         if ( temp->getID() > newID) {
         return temp;
         }

        while (temp->getNext()!= NULL){
           // go through the Node list
            int last=temp->getID();
            int next=temp->getNext()->getID();
            if (last<newID&&newID<next) 
            //return this node,insert at the middle
              return (temp);            
            temp = temp->getNext();
         }
        //now temp == NULL, at the end of the node list
        //insert at tail
        return (temp);  
}


bool NodeList::checkResName(string resName){
    
    Node* temp = head;
    while(temp != NULL){
        Resistor* resCheck = temp->getResHead()->getRH();
        while(resCheck!=NULL){
            if (resCheck->getName() == resName) return true;   
            //return true once find resistor has  the same name as the input resistor     
            resCheck=resCheck->getNext();
        }
        temp = temp->getNext();
    }
    return false;   
}

double NodeList::nodeVol(int nID){
    //given ID, fine the voltage of the node
    Node* temp = head;
    double nodeV = 0.0;
    while (temp!= NULL){
        //iterate through node list
        if (temp->getID() == nID) {
            nodeV = temp->getVoltage();
            return (nodeV);
        }
        temp = temp->getNext();       
    }   
}

void NodeList::printAllVal(){   
    //print voltage of all nodes
    Node* nodePtr = head;   
    while (nodePtr!=NULL) {      
        cout<< "Node "<< nodePtr->getID() << ": " <<fixed <<showpoint<<setprecision(2)<<nodePtr->getVoltage() << " V" <<endl;
        nodePtr = nodePtr->getNext();
    }   
}


Node* NodeList::findN(int ID){
    // return a Node pointer points to the node which given nodeID
    Node* nodePtr= head;
    while (nodePtr!=NULL){
        if (nodePtr->getID() == ID)
            return nodePtr;
        nodePtr = nodePtr->getNext();
    }
}

void NodeList::nodeFind(string resName, Node* &nodeA,int* place){
    
    Node* temp = head;   
    while(temp != NULL){
        Resistor* resCheck = temp->getResHead()->getRH();
        Resistor* ptr=NULL;
        while (resCheck != NULL) {            
            if (resCheck->getName() == resName) {
                nodeA = temp;
                *place = resCheck->getEnd(temp->getID());
                return;
            }
            resCheck = resCheck->getNext();
         }         
      temp = temp->getNext(); 
    }
    cout<<"Error: resistor" << resName <<" not found" <<endl;   
}

void NodeList::resPtr(string name){
   
    //print information of a resistor with given resistor name
    Node* temp = head;
    while(temp != NULL){
        Resistor* resCheck = temp->getResHead()->getRH();
        while(resCheck!=NULL){
            if (resCheck->getName() == name) {
                 cout<<"Print:"<<endl;
                   resCheck->printR();
                   return;
            }
            resCheck=resCheck->getNext();
        }
        temp = temp->getNext();
    }
    cout<<"Error: resistor " << name << " not found" <<endl;
    return;
}






