/*
 * Syntax_Check.cpp
 *
 *  Created on: 28.12.2014
 *      Author: anna
 */
#include "Syntax_Check.h"
#include "token.h"
#include "Automat.h"

using namespace std;

Syntax_Check::Syntax_Check(char* sourcefile){

	scannerpointer = new Scanner(sourcefile);
	actToken = scannerpointer->nextToken();
	failBit = CORRECT;
//    actToken=new  Token(ERROR,1,1);
	tokenType = actToken->getType();
	rootNode = new TreeNode(PROG);
	this -> prog();
}

Syntax_Check::~Syntax_Check(){

	delete scannerpointer;
	scannerpointer = 0;
}

void Syntax_Check::prog(){
	rootNode->nodeArray[0] = decls();
	if(failBit == CORRECT){
		rootNode->nodeArray[1] = statements();
	}
}

TreeNode* Syntax_Check::decls(){
	TreeNode* declsNode=0;
	if(tokenType == IDENTIFIER_INT){
		declsNode = new TreeNode(DECLS);
		declsNode->nodeArray[0] = decl();
		declsNode -> makeCode(DECLS);
			if(tokenType == OPERATOR_SEMICOL){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				declsNode->nodeArray[1] = decls();
			}
	}
	else if (tokenType == STRING || tokenType == IDENTIFIER_WRITE ||
			 tokenType == IDENTIFIER_READ || tokenType == OPERATOR_CUREVED_OPEN ||
			 tokenType == IDENTIFIER_IF || tokenType == IDENTIFIER_WHILE ||
			 tokenType == OPERATOR_SEMICOL || tokenType == EOF2){
		declsNode = new TreeNode(DECLS_EPS);
	}
	else{
		failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
			        cout << actToken -> getContainer() -> getValue() << endl;

	}
	return declsNode;
}

TreeNode* Syntax_Check::decl(){
	TreeNode* declNode = new TreeNode(DECL);
	if(tokenType == IDENTIFIER_INT){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		declNode->nodeArray[0] = array();
		if(tokenType == STRING){
		
		    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
		    declNode -> nodeArray[1] = leafe;
		
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}
		else{
				failBit = FAIL;
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
		 }
	}
	else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
	        cout << actToken -> getContainer() -> getValue() << endl;
	}
	return declNode;
}

TreeNode* Syntax_Check::array(){
	TreeNode* arrayNode=0;
	if(tokenType == OPERATOR_SQUERED_OPEN){
		arrayNode = new TreeNode(ARRAY);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		
		if(tokenType == NUMBER){
		
		    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
		    arrayNode -> nodeArray[0] = leafe;
		
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			if(tokenType == OPERATOR_SQUERED_CLOSED){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
			}
			else{
					failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
            		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else if(tokenType == STRING){
				failBit = FAIL;
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
		 }
		else{
			failBit = FAIL;
						cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
				        cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	else{
		arrayNode = new TreeNode(ARRAY_EPS);
	}
	return arrayNode;
}

TreeNode* Syntax_Check::statements(){
	TreeNode* statementsNode=0;
	if(tokenType == STRING || tokenType == IDENTIFIER_WRITE || tokenType == IDENTIFIER_READ
			|| tokenType == OPERATOR_CUREVED_OPEN || tokenType == IDENTIFIER_IF || tokenType == IDENTIFIER_WHILE){
		statementsNode = new TreeNode(STATEMENTS);
		statementsNode->nodeArray[0] = statement();
			cout  << "done" << endl;
			if(tokenType == OPERATOR_SEMICOL){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				statementsNode->nodeArray[1] = statements();
			}
	}
	else if (tokenType == EOF2){
		statementsNode = new TreeNode(STATEMENTS_EPS);
	}
	else{
		failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
			        cout << actToken -> getContainer() -> getValue() << endl;
	}
	return statementsNode;
}

TreeNode* Syntax_Check::statement(){

	TreeNode* statementNode = new TreeNode(STATEMENT);
	switch(tokenType){


	case STRING:{
	
	    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
	    statementNode -> nodeArray[0] = leafe;
	
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		statementNode->nodeArray[1] = index();
		if(tokenType == OPERATOR_DEFINITION){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			statementNode->nodeArray[2] = exp();
		}else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	break;


	case IDENTIFIER_WRITE:{
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			statementNode->nodeArray[0] = exp();
			if(tokenType == OPERATOR_BR_CLOSE){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
			}
			else{
				failBit = FAIL;
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	break;


	case IDENTIFIER_READ:{
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			if(tokenType == STRING){
			
			    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
		        statementNode -> nodeArray[0] = leafe;
			
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				statementNode->nodeArray[1] = index();
				if(tokenType == OPERATOR_BR_CLOSE){
					actToken = scannerpointer->nextToken();
					tokenType = actToken->getType();
				}
				else{
					failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
            		cout << actToken -> getContainer() -> getValue() << endl;
				}
			}
			else {
				failBit = FAIL;
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	break;



	case OPERATOR_CUREVED_OPEN:{
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		statementNode->nodeArray[0] = statements();
		if(tokenType == OPERATOR_CURVED_CLOSED){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}
		else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	break;


	case IDENTIFIER_IF:{
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			statementNode->nodeArray[0] = exp();
			if(tokenType == OPERATOR_BR_CLOSE){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				statementNode->nodeArray[1] = statement();
				if(tokenType == IDENTIFIER_ELSE){
					actToken = scannerpointer->nextToken();
					tokenType = actToken->getType();
					statementNode->nodeArray[2] = statement();
				}
				else{
					failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
            		cout << actToken -> getContainer() -> getValue() << endl;
				}
			}
			else{
				failBit = FAIL;
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	break;



	case IDENTIFIER_WHILE:{
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
		    actToken = scannerpointer->nextToken();
		    tokenType = actToken->getType();
			statementNode->nodeArray[0] = exp();
			if(tokenType == OPERATOR_BR_CLOSE){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				statementNode->nodeArray[1] = statement();
			}
			else{
				failBit = FAIL;
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	break;

	}
	return statementNode;
}

TreeNode* Syntax_Check::exp(){
	TreeNode* expNode = new TreeNode(EXP);

	expNode->nodeArray[0] = exp2();
	expNode->nodeArray[1] = op_exp();

	return expNode;
}

TreeNode* Syntax_Check::exp2(){
	TreeNode* exp2Node = new TreeNode(EXP2);

	if(tokenType == OPERATOR_BR_OPEN){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2Node->nodeArray[0] = exp();
		if(tokenType == OPERATOR_BR_CLOSE){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}
		else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}


	else if(tokenType == STRING){
	
	    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
	    exp2Node -> nodeArray[0] = leafe;
	
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2Node->nodeArray[1] = index();
	}


	else if(tokenType == NUMBER){
	
	    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
	    exp2Node -> nodeArray[0] = leafe;
	
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}


	else if(tokenType == OPERATOR_MINUS){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2Node->nodeArray[0] = exp2();
	}


	else if(tokenType == OPERATOR_EXCLAMATION){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2Node->nodeArray[0] = exp2();
	}

	else{
		failBit = FAIL;
		cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
		cout << actToken -> getContainer() -> getValue() << endl;
	}
	return exp2Node;
}

TreeNode* Syntax_Check::index(){
	TreeNode* indexNode;

	if(tokenType == OPERATOR_SQUERED_OPEN){
		indexNode = new TreeNode(INDEX);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		indexNode->nodeArray[0] = exp();
		if(tokenType == OPERATOR_SQUERED_CLOSED){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}else{
			failBit = FAIL;
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	else if(tokenType == OPERATOR_DEFINITION || tokenType == OPERATOR_BR_CLOSE){
		indexNode = new TreeNode(INDEX_EPS);
	}
	else{
		failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
			        cout << actToken -> getContainer() -> getValue() << endl;
	}

	return indexNode;
}

TreeNode* Syntax_Check::op_exp(){
	TreeNode* op_expNode=0;
	if(tokenType == OPERATOR_PLUS || tokenType == OPERATOR_MINUS || tokenType == OPERATOR_STAR ||
			tokenType == OPERATOR_SLASH || tokenType == OPERATOR_LESSTHAN ||
			tokenType == OPERATOR_MORETHAN || tokenType == OPERATOR_EQUAL ||tokenType == OPERATOR_UNEQUAL ||
			tokenType == OPERATOR_AMPERSAND){
		op_expNode = new TreeNode(OP_EXP);
		op_expNode->nodeArray[0] = op();
		op_expNode->nodeArray[1] = exp();
	}
	else if (tokenType == OPERATOR_SEMICOL || tokenType == OPERATOR_BR_CLOSE ||
			 tokenType == OPERATOR_SQUERED_CLOSED || tokenType == IDENTIFIER_ELSE){
		op_expNode = new TreeNode(OP_EXP_EPS);
	}
	else{
		failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
			        cout << actToken -> getContainer() -> getValue() << endl;
	}

	return op_expNode;
}

TreeNode* Syntax_Check::op(){
	TreeNode* opNode = new TreeNode(OP);
	if(tokenType == OPERATOR_PLUS){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_MINUS){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_STAR){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_SLASH){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_LESSTHAN){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_MORETHAN){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_EQUAL){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_UNEQUAL){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_AMPERSAND){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else{
		failBit = FAIL;
		cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
		cout << actToken -> getContainer() -> getValue() << endl;
	}
	return opNode;
}




int main(int argc,char* argv[]){
    cout << "start parser" << endl;
	Syntax_Check* syncheck = new Syntax_Check(argv[1]);
	cout << "end parser" << endl;
}




