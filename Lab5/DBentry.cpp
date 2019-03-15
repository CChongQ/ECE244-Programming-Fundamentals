/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DBentry1.cpp
 * Author: dell
 * 
 * Created on November 19, 2017, 12:39 AM
 */

#include "DBentry.h"
#include <iostream>
#include <cstdlib>

DBentry::DBentry(){
}
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}
DBentry::~DBentry(){
}

void DBentry::setActive(bool _active){
    active = _active;
}

void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}
void DBentry::setName(string _name){
    name = _name;
}
bool DBentry::getActive() const{
    return (active);
}
unsigned int DBentry::getIPaddress() const{
    return(IPaddress);
}
string DBentry::getName() const{
    return (name);
}
ostream& operator<< (ostream& out, const DBentry& rhs) {
    string status;
    if (rhs.active == true) 
        status = "active";
    else 
        status = "inactive";   
    out << rhs.name << " : " << rhs.IPaddress<< " : " << status; 
    return(out);    
}