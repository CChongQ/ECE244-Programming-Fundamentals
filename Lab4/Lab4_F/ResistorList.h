/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.h
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 6:19 PM
 */

#ifndef RESISTORLIST_H
#define RESISTORLIST_H
#include "Resistor.h"

class ResistorList{
    
private:
    Resistor* RLhead;
    
public:
   ResistorList();
   ~ResistorList();
   ResistorList(Resistor* newHead);
   
    Resistor* insertR();
    Resistor* getRH();
    void deleteRes(string resName);
    void deleteAllRes();   
    void setresHead(Resistor* newH);
    void modifyR(string name,double value,double &oldVal);      
};

#endif /* RESISTORLIST_H */

