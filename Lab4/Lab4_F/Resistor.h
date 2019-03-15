/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Resistor.h
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 6:09 PM
 */

#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
using namespace std;

class Resistor{
private:
    string name;
    double resistance;
    int endPoints[2];
    Resistor* Rnext;
public:
    Resistor();
    ~Resistor();
    Resistor(string newName,double value,int first,int second,Resistor* n);
    Resistor(string newName,double Resistance,int nodeOne,int nodeTwo);
    
    string getName();
    double getRes();;
    Resistor* getNext();
    void setNext(Resistor* newRes);
    int getEnd(int ID);
    void printR();
    void setResistance(double value);
   
};

#endif /* RESISTOR_H */

