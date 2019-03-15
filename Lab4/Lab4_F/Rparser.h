/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser_1.h
 * Author: qiuchenh
 *
 * Created on November 10, 2017, 1:43 PM
 */

#ifndef RPARSER_1_H
#define RPARSER_1_H
#include <string>
#include <iostream>
#include <iomanip>
#include "NodeList.h"
#include "Resistor.h"


    void insert(string inputString,NodeList* NodeHead);
    void setVoltage(string inputS,NodeList* &nodeHead);
    void solveNode(NodeList* &nodeHead);
    void unsetNode(string inputS,NodeList* &nodeHead);
    void deleteR(string inputS,NodeList* &nodeHead);
    void PrintRes(string inputS,NodeList* &nodeHead);
    void modifyRes(string inputS, NodeList* &nodeHead);
    void printNode(string inputLine,NodeList* &nodeHead);
    void exitFun(NodeList* nodeHead);
    void Rparser();
    


#endif /* RPARSER_1_H */

