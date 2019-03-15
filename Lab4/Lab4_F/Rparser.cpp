/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.cpp
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 6:43 PM
 */


#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

#include "Node.h"
#include "NodeList.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "Rparser.h"


using namespace std;


void insert(string inputString,NodeList* NodeHead){
    
    stringstream inputLine(inputString);
    string name;
    string command;
    double resistance;
    int nodeOne, nodeTwo;
    
    inputLine >> command;
    inputLine >> name;
    //Error check: whether the resistor name already exists
    //start from head of the node list, iterate through every node 
    if (NodeHead->checkResName(name) == false){       
    inputLine >> resistance;
    inputLine >> nodeOne >> nodeTwo;
        
        if (NodeHead->getHead() == NULL){   
        //entire node list is empty
        Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo);
        ResistorList* newResList = new ResistorList(newRes);
        Node* newNode = new Node(nodeOne,newResList);
        NodeHead->setHead(newNode);          
        }
        else {
         //nodeOne
            if ( (NodeHead->getHead()->getID()) > nodeOne ) {
            //insert at head
              Node* newNode = new Node(nodeOne,NodeHead->getHead());
              NodeHead->setHead(newNode);
              Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo);
              ResistorList* newResList = new ResistorList(newRes);
              newNode->setResHead(newResList);
            }
            else {
              bool where =false; 
              bool* tempW = &where;
              Node* place = NodeHead->findNode(nodeOne,tempW) ;   
              if (where == true){
                //insert in resistor in resistor list of the node "place"
                //i.e. input node already exists
                Resistor* resPlace =place->getResHead()->insertR();
                if (resPlace == NULL){
                   //this resistor will be head resistor
                   Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo);
                   place->getResHead()->setresHead(newRes);
                }
                else{
                  Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo,resPlace->getNext());
                  resPlace->setNext(newRes);
                }
           
              }
             else {
              //create a new node, behind place
              Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo);
              ResistorList* newResList = new ResistorList(newRes);
              Node* newNode = new Node(nodeOne,newResList);
              newNode->setNext(place->getNext());
              place->setNext(newNode);
             }
            }
        }
    
    //nodeTwo has the same logic as nodeOne
    if ( (NodeHead->getHead()->getID()) > nodeTwo) {
        //insert at head
        Node* newNode = new Node(nodeTwo,NodeHead->getHead());
        NodeHead->setHead(newNode);
        Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo);
        ResistorList* newResList = new ResistorList(newRes);
        newNode->setResHead(newResList);
    }
    else {
        bool where =false;
        bool* tempW = &where;
        Node* place = NodeHead->findNode(nodeTwo,tempW) ;   
        if (where == true){
            Resistor* resPlace =place->getResHead()->insertR();
            if (resPlace == NULL){
              Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo);
              place->getResHead()->setresHead(newRes);
            }
            else{
              Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo,resPlace->getNext());
             resPlace->setNext(newRes);
            }
            
        }
        else {
        //create a new node, behind place
          Resistor* newRes = new Resistor(name,resistance,nodeOne,nodeTwo);
          ResistorList* newResList = new ResistorList(newRes);
          Node* newNode = new Node(nodeTwo,newResList);
          newNode->setNext(place->getNext());
          place->setNext(newNode);
        }  
    } 
    
     
    cout << "Inserted: resistor " << name << " " << setprecision (2)<< fixed << resistance << " Ohms " << nodeOne << " -> " << nodeTwo<<endl;
    }
    else {
        cout <<"Error: the resistor "<< name << " already exists"<<endl;
        return;
    }
}

void setVoltage(string inputS,NodeList* &nodeHead){
    stringstream inputLine(inputS);
    int node;
    string command;
    double value;
    
    inputLine >> command >> node >> value;
    
    Node* temp = nodeHead->getHead();
    while(temp!= NULL){
      if (temp->getID() == node) {
          temp->setVoltage(value);
          temp->checkSet();
          cout<<"Set: node "<<node<< " to "<< value <<" Volts"<<endl;
          return;     
      }  
      temp = temp->getNext();      
    }
    cout <<"Error: node" << node << "not found" <<endl;
    return;
}

void solveNode(NodeList* &nodeHead){
    
    double MIN_ITERATION_CHANGE = 0.0001;
    bool checkMI = false;

    while (checkMI == false) {
        int countIT=0;
        int count=0;  
        int countSet=0;
        Node* tempNode = nodeHead->getHead();
        while (tempNode != NULL){
            countIT++;
            double oldV = tempNode->getVoltage();          
            if (tempNode->getResHead()->getRH() != NULL){
                //only solve voltage of a node when the resistor list of the node is not empty
                //i.e. node is connected with some resistors
               if (tempNode->checkV()==false){                                 
               //if the node does not have fixed voltage, calculate the node voltage
               //iterate through the resistor list   
                   Resistor* resPtr=tempNode->getResHead()->getRH();
                   double domi = 0;
                   double add = 0;
                   while (resPtr!=NULL){
                        double R = resPtr->getRes(); //resistance of each resistor
                        int otherNode = resPtr->getEnd(tempNode->getID());//ID of the other node which this resistor connected to
                        double otherVol = nodeHead->nodeVol(otherNode); // voltage of the other node
                        if(R==0 || otherVol == 0) {
                           //denominator cannot be 0
                           domi = domi;
                           add = add; 
                         }
                        else {
                          domi = domi+1/R; //domi is the denominator of (1/(1/R1+1/R2+1/R3+...))
                          add = add+(otherVol/R);  //add is equal to [V1/R1+V2/R2+V3/R3+...]
                        }
                    resPtr = resPtr->getNext();
                   }
            
                double newV=0;
                if (domi == 0 || add == 0){
                   newV=0;
                 }
                else {
                   newV= (1/domi)*add;
                 }
                double diff = abs(newV-oldV);
                if (diff < MIN_ITERATION_CHANGE ){
                 count++; 
                 }
               tempNode->setVoltage(newV);        
               }
               else{
                 countSet++; // this node has fixed voltage
                 countIT=countIT-1; 
               }
            }
            tempNode= tempNode->getNext(); 
        }
        
    if (countSet == 0){
        cout<< "Error: no nodes have their voltage set"<<endl;
       return;
     }
    
    if (countIT == count) //all nodes changes by no more than  MIN_ITERATION_CHANG
        checkMI = true; 
    
    }
                   
            
    cout <<"Solve:" <<endl;
    nodeHead->printAllVal(); 
  
     return;
}

void unsetNode(string inputS,NodeList* &nodeHead){
    stringstream inputLine(inputS);
    int node;
    string command;
    inputLine>>command>>node;
    
    //iterate through the node list to find the input node with input nodeID
    Node* temp = nodeHead->getHead();
    while(temp->getNext()!= NULL){
      if (temp->getID() == node) {
          temp->setVoltage(0.0);
          cout<<"Unset: the solver will determine the voltage of node " << temp->getID() <<endl;
          temp->unsetVC();
          return;     
      }  
      temp = temp->getNext();      
    }
    cout <<"Error: node "<< node <<" not found" <<endl;
    return;   
}

void deleteR(string inputS,NodeList* &nodeHead){
    
    string name;
    string command;
    stringstream inputLine(inputS);
    inputLine>>command>>name;
    
    if (name == "all"){
        Node* deleteHead=nodeHead->getHead();
        while (deleteHead!=NULL){
            deleteHead->getResHead()->deleteAllRes();
            deleteHead->setVoltage(0.0);
            deleteHead = deleteHead->getNext();
        }
        cout << "Deleted: all resistors" <<endl;
    }
    else{
        int place=-1; // "place" is the nodeID of the second node which this resistor is connected
        int* placeTBD=&place;
        //Firstly, determine whether the node exists
        //then delete them
        Node* nodeOne;
        nodeHead->nodeFind(name,nodeOne,placeTBD);
        if(place>=0) {
            //place >0 means that the node was found
            Node* nodeTwo = nodeHead->findN(place);
            nodeOne->getResHead()->deleteRes(name);
            nodeTwo->getResHead()->deleteRes(name);
            cout<<"Deleted: resistor " << name <<endl;                      
        }
        else return;                    
    }
}

void PrintRes(string inputS,NodeList* &nodeHead){
    string command;
    string name;
    stringstream inputLine(inputS);
    inputLine>>command>>name;
    nodeHead->resPtr(name);     
    return;
}

void modifyRes(string inputS, NodeList* &nodeHead){   
    string command;
    string name;
    double resistance;
    stringstream inputLine(inputS);
    inputLine>>command >> name >> resistance;
   
    //function Modify basically has the same logic as the print function   
    int secondN = -1;// "place" is the nodeID of the second node which this resistor is connected
    int* nextN = &secondN;
    Node* nodeOne;
    nodeHead->nodeFind(name,nodeOne,nextN);
    if (secondN >=0) {
       Node* nodeTwo = nodeHead->findN(secondN);
       double oldV=0;
       nodeOne->getResHead()->modifyR(name,resistance,oldV);
       nodeTwo->getResHead()->modifyR(name,resistance,oldV);   
       cout<<"Modified: resistor " << name << " from " << oldV << " Ohms "<< " to " << resistance <<" Ohms"<<endl;
    }
    else return;    
}

void printNode(string inputLine,NodeList* &nodeHead){    
    string command;
    int node;
    stringstream inputS(inputLine);
    
    inputS >> command >> node;
    if (inputS.fail()){
        // then the argument is "all" 
        cout<<"Print:"<<endl;
        Node* temp= nodeHead->getHead();
        while(temp != NULL){           
            temp->printN();
            temp  = temp->getNext();
        }        
    }
    else{
        //argument is nodeID
        cout<<"Print:"<<endl;
        Node* nodeF = nodeHead -> findN(node);   
       nodeF->printN();
    }
       
}

void exitFun(NodeList* nodeHead){
    //before exiting main function, need to delete all dynamically allocate memories
    // the order: Resistor -> ResistorList -> Node -> NodeList
    Node* temp = nodeHead->getHead();
    while (temp != NULL) {
        Resistor* resH = temp->getResHead()->getRH();
        ResistorList* deleteRL = temp->getResHead();
        while (resH != NULL) {
            Resistor* tptr = resH;
            deleteRL->setresHead(resH->getNext());
            resH = resH->getNext();
            delete tptr; //delete resistor
        }
        delete deleteRL; //delete ResistorList
        Node* nodePtr = temp;
        nodeHead->setHead(temp->getNext());
        temp = temp->getNext();
        delete nodePtr; //delete node
        nodePtr = NULL;
    }
    
}

void Rparser(){

    string inputLine;
    string command;
    NodeList* nodeHead = new NodeList();
    cout << "> ";      
    getline(cin,inputLine); 
    stringstream inputS(inputLine);
    
    inputS>>command;
 
    while (!cin.eof()) {
        stringstream inputString(inputLine);
        inputString>>command;
       if(command == "insertR") {
           insert(inputLine,nodeHead);
       }
       else if (command == "setV") {
           setVoltage(inputLine,nodeHead);
       }
       else if (command =="unsetV"){
           unsetNode(inputLine,nodeHead);
       }
       else if (command =="solve"){
           solveNode(nodeHead);
       }
       else if (command == "deleteR"){
           deleteR(inputLine,nodeHead);
       }
       else if (command == "printR") {
           PrintRes(inputLine,nodeHead);
       }
       else if (command == "modifyR"){
           modifyRes(inputLine,nodeHead);
       }
       else if(command == "printNode"){
           printNode(inputLine,nodeHead);
       }
       else{
           cout<<"Invalid output" << endl;
       }
        cout << ">";      
        getline(cin,inputLine);  
     //end input loop until EOF
     }
    exitFun(nodeHead);
    delete nodeHead;
    return;
}