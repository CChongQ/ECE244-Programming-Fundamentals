/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: qiuchenh
 *
 * Created on November 8, 2017, 6:08 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include "Resistor.h"
using namespace std;

Resistor::Resistor(){
}
Resistor::~Resistor(){
}
Resistor::Resistor(string newName,double value, int first, int second, Resistor* n){
    //initialize the resistor
    name = newName;
    resistance = value;
    endPoints[0]=first;
    endPoints[1]=second;
    Rnext = n;   
}

Resistor::Resistor(string newName,double Resistance,int nodeOne,int nodeTwo){
    name = newName;
    resistance = Resistance;
    endPoints[0]=nodeOne;
    endPoints[1]=nodeTwo;
    Rnext = NULL;
   
}
string Resistor::getName(){
    return (name);
}
double Resistor::getRes(){
    return resistance;
}

Resistor* Resistor::getNext(){   
    return (Rnext);
}

void Resistor::setNext(Resistor* newRes){   
    Rnext = newRes;
}
int Resistor::getEnd(int ID){ 
    if (endPoints[0]==ID) return (endPoints[1]);
    else return(endPoints[0]);
    
}

void Resistor::printR(){  
    cout<<setw(20)<<left<<name << setw(8)<<right <<fixed <<showpoint<<setprecision(2)<<resistance
            <<" Ohms " <<endPoints[0]<<" -> " <<endPoints[1]<<endl;   
}

void Resistor::setResistance(double value){
   
    resistance = value;
}