/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 7:35 PM
 */

#ifndef NODE_H
#define NODE_H
#include "Resistor.h"
#include "ResistorList.h"

class Node {
private:
    int nodeID;
    Node* Nnext;
    ResistorList* headR;
    double voltage = 0;
    bool setV = false;

public:
    Node();
    ~Node();
    Node(int value, Node* newNode);
    Node(int value,ResistorList* newRes);
    
    Node* getNext();
    void setVoltage(double value);
    double getVoltage();
    int getID();
    void setNext( Node* newNode);
    void setResHead(ResistorList* newHead);
    ResistorList* getResHead();
    bool checkV();
    void checkSet();
    void unsetVC();
    void printN();  
};

#endif /* NODE_H */

