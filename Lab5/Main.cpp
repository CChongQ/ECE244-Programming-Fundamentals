/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dell
 *
 * Created on November 19, 2017, 12:36 AM
 */

#include <cstdlib>
#include <sstream>
#include <iostream>
#include "TreeDB.h"

using namespace std;


void insertNode(string inputLine, TreeDB* &bstRoot){
    stringstream inputStream(inputLine);
    string command;
    string name;
    string inputSta;
    unsigned int IPaddress;
    bool status;
    inputStream>> command >> name >> IPaddress >> inputSta;
    
    if (inputSta == "active") {
        status = true;
    }
    else status = false;
    
    DBentry* newInfo = new DBentry(name, IPaddress, status);
    bool check = bstRoot->insert(newInfo);
    if (check == false){
        //there already exists an entry with the same key
        cout << "Error: entry already exists" <<endl;
        delete newInfo;
        return;
    }
    else {
        cout<<"Success" <<endl;
        return;
    }  
}

void findNode(string inputLine,TreeDB* &bstRoot){
    string command;
    string name;
    stringstream inputS(inputLine);
    inputS >> command >> name;
    DBentry* tempFind = bstRoot->find(name);
    if (tempFind == NULL){
        cout << "Error: entry does not exist" <<endl;
        return;
    }
    else {
        //entry exists
        string status;
        if (tempFind->getActive() == true)
            status = "active";
        else status = "inactive";
        cout << tempFind->getName() << " : " << tempFind->getIPaddress() << " : "
                << status <<endl;
        return;
    }
        
}

void removeNode(string inputLine, TreeDB* &bstRoot){
    string command;
    string name;
    stringstream inputS (inputLine);
    inputS >> command >> name;
    bool result = bstRoot->remove(name);
    
    if (result == true){
        cout << "Success" <<endl;
        return;
    }
    if (result == false){
        cout <<"Error: entry does not exist" <<endl;
        return;
    }   
}

void removeAll(TreeDB* &bstRoot){
    bstRoot->clear();
    cout << "Success" <<endl;
    return;
}

void printAll(TreeDB* bstRoot) {
    cout << (*bstRoot);  
    return;
}
void printProbes(string name,TreeDB* bstRoot) {    
    DBentry* temp = bstRoot->find(name);
    if (temp == NULL){
        cout << "Error: entry does not exist" <<endl;
        return;
    }
    else{
        bstRoot->printProbes();
        return;
    }
}
void countActive(TreeDB* bstRoot){
    bstRoot->countActive();
    return;
}
void updates(TreeDB* bstRoot,string name, string status){    
    DBentry* temp = bstRoot->find(name);
    if (temp == NULL){
        cout << "Error: entry does not exist" <<endl;
        return;
    }
    else{
        bool set = true;
        if (status == "active") 
            set = true;
        else 
            set = false;
        temp->setActive(set);
        cout <<"Success" <<endl;
        return;
    }
}
void exitMain(TreeDB* bstRoot){
    bstRoot->clear();
    return;
}
int main(int argc, char** argv) {
    string command;
    string inputLine;
    
    TreeDB* bstRoot = new TreeDB();
    
    cout<<"> ";
    getline(cin,inputLine);  
   stringstream inputStream(inputLine);
    while(!cin.eof()){
        stringstream inputStream(inputLine);
        inputStream>>command;
        if(command == "insert"){
            insertNode(inputLine, bstRoot);           
        }
        else if (command == "find"){
            findNode(inputLine,bstRoot);
        }
        else if (command == "remove"){
           removeNode(inputLine,bstRoot);   
        }
        else if (command == "removeall"){
            removeAll(bstRoot);
        }
        else if (command == "printall"){
            printAll(bstRoot);
        }
        else if (command == "printprobes"){
            string name;
            inputStream>>name;
            printProbes(name,bstRoot);              
        }
        else if (command == "countactive"){
            countActive(bstRoot);
        }
        else if (command == "updatestatus"){
            string name;
            string status;
            inputStream >> name >>status;
            updates(bstRoot,name,status);
        }
        else {
            cout<<"invalid input"<<endl;
        }  
        cout<<"> ";
        getline(cin,inputLine);         
    } 
   exitMain(bstRoot);
   delete bstRoot;  
   return 0;
}

