/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.cpp
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 6:28 PM
 */

#include <cstdlib>
#include "ResistorList.h"
#include "Resistor.h"

using namespace std;

ResistorList::ResistorList(){
    RLhead = NULL;
}
ResistorList::~ResistorList(){
}

ResistorList::ResistorList(Resistor* newHead){
    RLhead = newHead;
}

Resistor* ResistorList::insertR (){
    Resistor* temp = RLhead;
    if (temp == NULL) {
        //insert head
        return(temp);
    }
    while(temp->getNext() != NULL) {

        temp = temp->getNext();        
    }
    return (temp);       
}

Resistor* ResistorList::getRH(){
    return (RLhead);
}

void ResistorList::deleteRes(string resName){   
    if (RLhead == NULL) {
        // this resistor list is empty
        return;
    }
    Resistor* temp = RLhead;
    Resistor* ptr = NULL;
    while (temp != NULL) {
        if (temp->getName() == resName) 
            break;
        ptr = temp;
        temp = temp->getNext(); 
    }
    
    // temp is the place to de deleted
    if (temp == NULL) {
        // resistor was not found
        cout << "Error: resistor " << resName << "not found"<<endl;
        return;
    }
    if (temp == RLhead) {
        //delete head
        RLhead = RLhead->getNext();
        delete temp;
        return;
    }
    ptr->setNext(temp->getNext());
    delete temp;  
    temp = NULL;    
    return;
}

void ResistorList::deleteAllRes(){   
    Resistor* temp = RLhead;
    while(temp != NULL){
        RLhead = RLhead->getNext();       
        Resistor* tptr = temp;
        temp = RLhead;    
        delete tptr;
        tptr = NULL;
    }
   
}

void ResistorList::setresHead(Resistor* newH){
    RLhead = newH;
}

void ResistorList::modifyR(string name,double value,double &oldVal){
    Resistor* temp=RLhead;
    while(temp != NULL){
        //modify the value
        if(temp->getName() == name){
            oldVal = temp->getRes();
           temp->setResistance(value);
           return;
        }
        temp = temp->getNext();
    }
}





