/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeNode1.cpp
 * Author: dell
 * 
 * Created on November 19, 2017, 12:40 AM
 */

#include "TreeNode.h"

TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}
TreeNode::~TreeNode(){
    delete entryPtr;
    entryPtr = NULL;
}

void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}
void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}
TreeNode* TreeNode::getLeft() const{
    return (left);
}
TreeNode* TreeNode::getRight() const{
    return (right);
}
DBentry* TreeNode::getEntry() const{
    return (entryPtr);
}
