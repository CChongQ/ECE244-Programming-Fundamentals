/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.h
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 7:39 PM
 */

#ifndef NODELIST_H
#define NODELIST_H
#include "Node.h"
#include "Resistor.h"

class NodeList {
private:
    Node* head;
public:
    NodeList();
    ~NodeList();
    NodeList(Node* newHead);
    
    void setHead(Node* newHead);
    Node* getHead();
    
    Node* findNode(int newID,bool* where);
    bool checkResName(string resName);
    double nodeVol(int nID);
    void printAllVal();
    Node* findN(int ID);
    void nodeFind(string resName, Node* &nodeA,int* place);
    void resPtr(string name);
    
    
};


#endif /* NODELIST_H */

