/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeDB1.cpp
 * Author: dell
 * 
 * Created on November 19, 2017, 12:39 AM
 */

#include "TreeDB.h"
#include <sstream>
#include <iostream>
#include <cstdlib>


using namespace std;

bool TreeDB::insert_bst(TreeNode* r, DBentry* newEntry){
    string nodeKey = r->getEntry()->getName();
    string newKey = newEntry->getName();
    
    if ( nodeKey == newKey){
        //node with the same key as newEntry
        return (false);
    }
    int result = nodeKey.compare(newKey);
   
    if (result>0 ){
    //key of node is greater than that of new key,
    //traverse left
        if(r->getLeft() == NULL) {
            //insert at r->left
            TreeNode* newNode = new TreeNode(newEntry);
            r->setLeft(newNode);
            return (true);
        }
        else {
            return (insert_bst(r->getLeft(),newEntry));          
        }     
    }
     
    if(result<0){
        //the key of node is less than that of newKey
        //traverse right
        if(r->getRight() == NULL){
            //insert at right side
            TreeNode* newNode = new TreeNode(newEntry);
            r->setRight(newNode);
            return (true);
        }
        else {
            return (insert_bst(r->getRight(),newEntry));
        }
    }   
}

void TreeDB::clear_bst(TreeNode* r){
    //delete left subtree firstly, then delete right subtree      
    if (r != NULL){
       clear_bst(r->getLeft());
       clear_bst(r->getRight());
       //delete the treeNode
        DBentry* tempPtr = r->getEntry();
        delete r;
        r = NULL; 
    }
    return;
}

DBentry* TreeDB::find_bst(string name,TreeNode* tempTN){
    string nameT = tempTN->getEntry()->getName(); //namtT is the key of current entry
    DBentry* tempPtr;
    if (nameT.compare(name) == 0){
        //the entry is found,return a pointer to it
        probesCount++;
        return(tempTN->getEntry());
    }
    else if (nameT.compare(name) <0 ){
        probesCount++;
        //input key is greater than node key
        //traverse right
        if (tempTN->getRight() == NULL)
            return (NULL);
        else {
            tempPtr = find_bst(name,tempTN->getRight());
        }
    }
    else{
        //input key is less than node key
        //tranverse left
        probesCount++;
        if (tempTN->getLeft() == NULL)
            return (NULL);
        else {
            tempPtr = find_bst(name,tempTN->getLeft());
        }
    }
    return (tempPtr);   
}

TreeNode* TreeDB::remove_re(TreeNode* nodePre){
    //find a node to replace the deleted node with maximum node in the left subtree method 
    //return the parent of this node,then the node to be delete is parent->right
    if (nodePre->getRight() == NULL)
        return (nodePre);    
    if (nodePre->getRight()->getRight() == NULL )
        return (nodePre);
    else {
        return ( remove_re(nodePre->getLeft()) );
    }    
}

bool  TreeDB::remove_bst(string name, TreeNode* deleteNode,TreeNode* deletePre,int a){        
    string nodeName = deleteNode->getEntry()->getName();    
    if (deleteNode == NULL){
        return (false);
    }
    else if (deleteNode == root){
        if (nodeName == name) {
        //delete root
            if (root->getLeft() ==NULL && root->getRight() == NULL) {
              //this bst has only one node
              delete root;
              root = NULL;
              return(true);
            }
            else if(root->getLeft() == NULL && root->getRight() != NULL){
              //this bst has only 2 nodes, root and root->right;
              root = root->getRight();
              delete deleteNode;
              return (true);
             }
          TreeNode* newNodePre = remove_re(root->getLeft());
          TreeNode* newNode = newNodePre->getRight();
          if (newNode == NULL){
             //this bst has only three node
              newNode = newNodePre; //newNode is root->left
              root = newNode;
              newNode->setRight(deleteNode->getRight());
              delete deleteNode;
              return (true);
          }         
          else {
             TreeNode* newNodeLeft = newNode->getLeft();;
             //newNode->right is NULL, so newNode's parent->right should be newNode->left
             root = newNode;
             newNode->setLeft(deleteNode->getLeft());
             newNode->setRight(deleteNode->getRight());
             newNodePre->setRight(newNodeLeft);
             delete deleteNode;
             return (true);
          }
        }
        else {
            if (nodeName.compare(name) <0 ){//traverse right
              return (remove_bst(name,deleteNode->getRight(),deleteNode,2));
            }
            else {//traverse left
               return(remove_bst(name,deleteNode->getLeft(),deleteNode,1));
            }     
         }
        
    }
    
    //delete interior nodes
    else if (nodeName == name) {
        if(a==1){
            //the deleted node is on the left side of its parent
            if (deleteNode->getLeft() ==NULL && deleteNode->getRight() == NULL) {
              // the node to be delete does not have children
              deletePre->setLeft(NULL);
              delete (deleteNode);
              return(true);
             }
            else if(deleteNode->getLeft() == NULL && deleteNode->getRight() != NULL){
             // the node to be delete only has right child
            //newNode will the the right child
              deletePre->setLeft(deleteNode->getRight());
              delete deleteNode;
              return (true);
            }
            TreeNode* newNodePre = remove_re(deleteNode->getLeft());
            TreeNode* newNode = newNodePre->getRight();
            if (newNode == NULL){  
                //In this case newNodePre == deleteNode, newNode == NULL
                // which means that the left child of the deleteNode does not have any child 
                //newNode should be deleteNode->left
                newNode = newNodePre;
                deletePre->setLeft(newNode);
                newNode->setRight(deleteNode->getRight());
                delete deleteNode;
                return (true);
            }     
            else { 
                //before delete this node, set its parent's left to be newNode
                   TreeNode* newNodeLeft = newNode->getLeft();
                   deletePre->setLeft(newNode);
                   newNode->setLeft(deleteNode->getLeft());
                   newNode->setRight(deleteNode->getRight());              
                   newNodePre->setRight(newNodeLeft);
                   delete deleteNode;
                   return (true);
                
            }        
        }
        
    if (a==2) {
        //the node to be delete is on the right side of the pre node
        //Logic of this case is similar as the previous one, the only difference is that
        //set right child of the deleteNode's parent to be newNode      
            if (deleteNode->getLeft() ==NULL && deleteNode->getRight() == NULL) {
              // the node to be delete does not have children
              deletePre->setRight(NULL);
              delete (deleteNode);
              return(true);
             }
            else if(deleteNode->getLeft() == NULL && deleteNode->getRight() != NULL){
             // the node to be delete only has right child
             //newNode will the the right child
              deletePre->setRight(deleteNode->getRight());
              delete deleteNode;
              return (true);
             }
            TreeNode* newNodePre = remove_re(deleteNode->getLeft());
            TreeNode* newNode = newNodePre->getRight();
            if (newNode == NULL){  
                //newNode should be deleteNode->left
                newNode = newNodePre;
                deletePre->setRight(newNode);
                newNode->setRight(deleteNode->getRight());
                delete deleteNode;
                return (true);
            }     
            else {
                //before delete this node, set its parent's right to be newNode
                TreeNode* newNodeLeft = newNode->getLeft();
                deletePre->setRight(newNode);
                newNode->setLeft(deleteNode->getLeft());
                newNode->setRight(deleteNode->getRight());              
                newNodePre->setRight(newNodeLeft);
                delete deleteNode;
                return (true);
            }        
        }
        
    }
    else {
        if (nodeName.compare(name) <0 ){//traverse right
            return (remove_bst(name,deleteNode->getRight(),deleteNode,2));
        }
        else {//traverse left
            return (remove_bst(name,deleteNode->getLeft(),deleteNode,1));
        }     
    }
}

TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}
TreeDB::~TreeDB(){

}

bool TreeDB::insert(DBentry* newEntry){
    if (root == NULL){
        //newEntry will be the root
        root = new TreeNode(newEntry);
        root->setLeft(NULL);
        root->setRight(NULL);
        return (true);
    }
    else {
        //this bst has at least one node
        bool result = insert_bst(root, newEntry);
        return (result);
    }  
}

DBentry* TreeDB::find(string name){
    if(root == NULL)
        return(NULL);
    probesCount = 0;
    DBentry* tempP = find_bst(name, root);
    return (tempP);   
}

bool TreeDB::remove(string name){
    bool result = remove_bst(name, root, NULL,1);
    return result;  
}

void TreeDB::clear(){
    clear_bst(root);
    root = NULL;
}

void TreeDB::printNode(TreeNode* newNode){
    if (newNode != NULL){
        //use in-order traversal, traverse left, visit the node, print the node, then traverse right
        printNode(newNode->getLeft());
         DBentry* temp= newNode->getEntry();
         cout << (*temp) <<endl;
        printNode(newNode->getRight());
    }
}
ostream& operator<< (ostream& out, TreeDB& rhs){
    TreeDB* temp = &rhs;
   TreeNode* head = rhs.root;
    if ( head != NULL) 
        temp->printNode(head);     
}
void TreeDB::printProbes() const{
    
    cout << probesCount<<endl;
}
void TreeDB::countActive() const{
    TreeNode* temp = root;
    int count = 0;
    countAC(temp,count);
    cout << count <<endl;   
}

void TreeDB::countAC( TreeNode* node, int &count) const{
    //use in-order traversal
    if (node != NULL){
        countAC(node->getLeft(),count);
        if (node->getEntry()->getActive() == true) count++;
        countAC(node->getRight(),count);
    }
    return;
}
   