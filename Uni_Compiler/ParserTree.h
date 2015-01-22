/*
 * Node.h
 *
 *  Created on: 08.01.2015
 *      Author: anna
 */

#ifndef NODE_H_
#define NODE_H_

#include "superTreeNode.h"
#include "nodeTypes.h"
using namespace std;


class TreeNode : public SuperTreeNode{

public:
	
	
	TreeNode(Rule nodeRule);
	~TreeNode();
	Container* getContainer();
	void setNodeType(NodeType);
	NodeType getNodeType();

private:
    NodeType type;
	
	

};


#endif /* NODE_H_ */
