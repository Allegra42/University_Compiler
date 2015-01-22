/*
 * Node.cpp
 *
 *  Created on: 08.01.2015
 *      Author: anna
 */

#ifndef _NODE_CPP_
#define _NODE_CPP_

#include "ParserTree.h"

TreeNode::TreeNode(Rule nodeRule){
	this->nodeRule = nodeRule;
	this->setNodeType(NO_TYPE);
}


TreeNode::~TreeNode(){
	if (nodeArray[0]) delete nodeArray[0];
	if (nodeArray[1]) delete nodeArray[1];
	if (nodeArray[2]) delete nodeArray[2];
}

Container* TreeNode::getContainer(){
    cout << "DESTROY" << endl;
    return 0;
}

void TreeNode::setNodeType(NodeType nodeType){
    this -> type = nodeType;
}

NodeType TreeNode::getNodeType(){
    return type;
}

#endif



