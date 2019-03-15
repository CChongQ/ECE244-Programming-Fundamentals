/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: qiuchenh
 *
 * Created on October 5, 2017, 11:48 AM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#define MAX_NODE_NUMBER 5000

using namespace std;


bool nodeCheck (int node) {
    //this function is used to check the range of node, which should be 0-5000
    // return true when it's out of range
     if ( (node >MAX_NODE_NUMBER) || node < 0 ) {
            cout << "Error: node " << node << " is out of permitted range 0-5000" << endl;
            return true;
        }  
     else {
         return false;
     }    
}

void insert(string inputLine) {
    string input;
    string resistor;
    double resistorValue;
    string nodeOne;
    string nodeTwo;
    string checkNode;
    
    stringstream lineStream(inputLine);
    lineStream >> input;   
       if (lineStream.eof()) { 
          cout << "Error: too few arguments" << endl;
          return;
        }
        if (lineStream.fail()) {
          cout << "Error: invalid argument" <<endl;
           return;       
        }

    //resistor name check
    lineStream >> resistor;
        if (lineStream.eof()) { 
          cout << "Error: too few arguments" << endl;
          return;
        }
        if (lineStream.fail()) {
          cout << "Error: invalid argument" <<endl;
          return;       
        }  
        if (resistor == "all") {
           cout << "Error: resistor name cannot be the keyword" << '"' << "all" << '"' << endl;
           return;
        }  
    
    //resistor value check
    lineStream >> resistorValue;
         if (lineStream.eof()) {
           cout << "Error: too few arguments" << endl;
            return;
         }
        if (lineStream.fail()) {
            cout << "Error: invalid argument" <<endl;
           return;
         }
        if (resistorValue < 0.0) { //resistor value should be greater than 0
           cout << "Error: negative resistance" <<endl;
            return;
         }
   
    //first node
    lineStream >> nodeOne;
        stringstream temp1(nodeOne);      
        int nodeOneT = -1;
          temp1 >> nodeOneT;
        bool On1=temp1.fail(); 
        int checkNodeEnd1 = temp1.peek();
     
       if (lineStream.eof()) {
           cout << "Error: too few arguments" << endl;
            return;
        }
        if (On1 == true || checkNodeEnd1 != -1) {
         //type of the node is incorrect,eg.node is not an integer
            // or node is in the format like "10node"
           cout << "Error: invalid argument" <<endl;
           return;
        }
        if (nodeCheck(nodeOneT)) {
           return;
         }
    
     //second node
     lineStream >> nodeTwo;
        stringstream temp2(nodeTwo);
        int z=temp2.peek(); 
        int nodeTwoT = -100;      
        temp2 >> nodeTwoT;
        bool check=temp2.fail();
        int checkNodeEnd2 = temp2.peek();
        
        if ( z==-1 && (check || checkNodeEnd2 == -1)) {  
            //the node is a white space or user didn't input the value of node2
            cout <<"Error: too few arguments" << endl;
            return;          
        }
        else {        
            if (lineStream.fail() || check ||checkNodeEnd2 !=-1) {       
                //checkNodeEnd2 !=-1: is used to check the format of the second node
                cout << "Error: invalid argument" << endl;
                return;
             }
            else {
                if (nodeCheck(nodeTwoT)) {
                   return;
                 }
                if (nodeOneT == nodeTwoT) {
                  cout << "Error: both terminals of resistor connect to node " << nodeTwo <<endl;
                  return;
                 }  ; 
            }
        }   
        if (!lineStream.eof()) {
            lineStream >> checkNode;
            stringstream temp2(checkNode); 
            int c=temp2.peek();
            if (c == -1) {
                //the rest of the string are white spaces
                lineStream.ignore(1000,'\n');                
            } 
            else {
                //too many arguments
                cout << "Error: too many arguments" << endl;
               return;
            }                      
        }
        
    //input satisfy all requirements, there are no errors
    cout << "Inserted: resistor " << resistor << " " << setprecision (2)<< fixed << resistorValue << " Ohms " << nodeOne << " -> " << nodeTwo <<endl;
    return;    
}

void modify(string inputLine) {
    string input;
    string resistor;
    string resistorValue;
    string checkNode;
    double resistance = -2.0;

    stringstream lineStream(inputLine);
    //command check
    lineStream >> input;    
        if (lineStream.eof()) { 
            cout << "Error: too few arguments" << endl;
            return;
        }  
        if (lineStream.fail()) {
          cout << "Error: invalid argument" <<endl;
          return;
         }    
        
    //name check
    lineStream >>resistor;
        if (lineStream.eof()) { 
            cout << "Error: too few arguments" << endl;
            return;
        }   
        if (lineStream.fail()) {
          cout << "Error: invalid argument" <<endl;
          return;
         }  
        if (resistor == "all") {
           cout << "Error: Error: resistor name cannot be the keyword " << '"' << "all" << '"' << endl;
           return;
        } 
 
    //resistor value check
    lineStream >> resistorValue;
        stringstream temp1(resistorValue);
        temp1 >> resistance;
        bool On1=temp1.fail(); 
        int checkValueEnd1 = temp1.peek();
                   
        if ( lineStream.fail() || On1 || checkValueEnd1 !=-1) {
          cout << "Error: invalid argument" <<endl;
          return;
        } 
        
        if (On1){ 
            cout <<"Error: too few arguments" << endl;
            return;
         }  
        if (resistance < 0.0) { //resistor value should be greater than 0
           cout << "Error: negative resistance" <<endl;
            return;
         }
         if (!lineStream.eof()) {
            int c = lineStream.peek();
            lineStream >> checkNode;
            if (c>0 && !lineStream.fail()) {
               cout << "Error: too many arguments" << endl;
               return;
            }
            else {
                lineStream.ignore(1000,'n');              
            }
         }          
    
    //there are no errors
    cout << "Modified: resistor " << resistor << " to " << setprecision (2)<< fixed <<resistance << " Ohms" <<endl;
    return;
}

void print(string inputLine) {
    //print should only have one argument, "all" or resistor name
    string input;
    string resistor;
    stringstream lineStream(inputLine);
    string checkNode;
   
    lineStream >>input;
        if (lineStream.eof()) {
          cout << "Error: too few arguments" << endl;
          return;
        }
   
    //name 
    lineStream >> resistor;
    stringstream temp(resistor);
    int x= temp.peek();

        if (x==-1 || x==32) {
            //x==32: white space
            //x==-1:enter key 
          cout << "Error: too few arguments" <<endl;
          return;
         }
        if (lineStream.fail()){          
             cout << "Error: invalid argument" <<endl;
             return;
         }  
        if (!lineStream.eof()) {
            int c = lineStream.peek();
            lineStream >> checkNode;
            string nextNode;
            stringstream tempW(checkNode);
            int m=tempW.peek();
            
            if ( (c!=32&& c!= -1) || m!=-1 ) {
               cout << "Error: too many arguments" << endl;
               return;
            }
            else{
                lineStream.ignore(1000,'\n');
            }
         }    
          
    if (resistor == "all") {
        cout << "Print: all resistors" <<endl;
        return;
    }    
    else {    
        cout << "Print: resistor " << resistor << endl;
        return;
    }    
}
    


void printNode (string inputLine) {
    string input;
    stringstream lineStream(inputLine); 
    stringstream lineStreamTwo(inputLine); 
    string node;
    int nodeInt = -2;

    string nextNode;
    
    lineStream >> input;
        if (lineStream.eof()) {
        cout << "Error: too few arguments" << endl;
            return;
         }
    
    //node
    lineStream >> nodeInt;  
        if (lineStream.fail()) {
            // then the node is not an integer
            //check whether it's "all" or not
            lineStreamTwo >> input >> node;
               stringstream temp(node);
                int x= temp.peek();
                if (x ==-1 || x==21){
                    cout << "Error: too few arguments" << endl;
                    return;
                }
            if (lineStreamTwo.fail()) {
                //then the input neither characters nor an integer
                cout << "Error: invalid argument" <<endl;
                return;               
            }
            else {
                //input are characters, then check whether its name is all or not
                 if (node == "all") {
                     if (!lineStreamTwo.eof()) {
                         int c = lineStreamTwo.peek();
                         if (c != -1) {
                             cout << "Error: too many arguments" << endl;
                             return;
                         }    
                     }
                     else {
                         cout << "Print: all nodes" <<endl;
                         return;
                    }   
                 }
                 else {
                     //a string other than all have been entered where all is expected
                     cout << "Error: invalid argument" <<endl;
                     return;
                 }                 
            }
         } 
         
        else {
            //node is an integer, continue use nodeInt
            bool condition = lineStream.fail();
            int checkNodeEnd =lineStream.peek();
            lineStream>>nextNode;
            stringstream temp(nextNode);
            int nextNodeEnd = temp.peek();
            
            if ( condition || (checkNodeEnd != -1 && checkNodeEnd !=32)) {
            //incorrect 
            //or node is not an integer
            cout << "Error: invalid argument" <<endl;
            return;
            }
            if (nodeCheck(nodeInt)) {
                // node value is out of range
                return;
            }
            if ( nextNodeEnd != -1 || !lineStream.eof()){
                  cout << "Error: too many arguments" << endl;
                  return;
            }
            else {
                  lineStream.ignore(1000,'\n');
              }

            //node value is in the range
             if (!lineStream.eof()) { 
                   cout << "Error: too many arguments" << endl;
                   return;
              }  
             else{ 
                 cout << "Print: node " << nodeInt <<endl;
                return;
            }         
        }                     
}
void deleteN(string inputLine) { 
    //argument should be "all" or a resistor's name
    string input;
    stringstream lineStream(inputLine);
    string resistor;
     
    lineStream >> input;
         if (lineStream.eof()) {
            cout << "Error: too few arguments" <<endl;
            return;
         }
   
    lineStream >> resistor;
     stringstream temp(resistor);
     int x= temp.peek();
         if (x ==-1 || x==32) {
            cout << "Error: too few arguments" <<endl;
            return;
          }
         if (lineStream.fail()) {
          cout << "Error: invalid argument" <<endl;
          return;
         }
        if (!lineStream.eof()) { 
            cout << "Error: too many arguments" << endl;
            return;
         }
     if (resistor == "all") {
        cout << "Deleted: all resistors" << endl;
        return;
     }
     else {
        cout << "Deleted: resistor " << resistor << endl;
        return;
     }
    
}

int main(int argc, char** argv) {
    string inputLine;
    string command;
    
    
    cout << ">";
    getline(cin,inputLine);
    while (!cin.eof()) {
        stringstream lineStream(inputLine);
        lineStream >> command;
        
        if(command == "insertR") {
            insert(inputLine);
        }
        
        else if (command == "modifyR"){
            modify(inputLine);
        }
        
        else if (command == "printR") {
            print(inputLine);
        }
        
        else if(command == "printNode"){
            printNode(inputLine);
        }
            
        else if (command == "deleteR") {
            deleteN(inputLine);
        }
        
        else {
            cout << "Error: invalid command" <<endl;
        }
    cout << ">";
     getline (cin,inputLine);
    }  //end input loop until EOF
    return 0;   
}

