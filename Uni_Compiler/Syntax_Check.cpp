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

/**
 * Syntax_Check nimmt einen Quelltext entgegen, führt diesen dem
 * Scanner zu, der diesen einließt, sinnvolle Tokens bildet und diese
 * über eine Hashmap verwaltet; danach wird die Eingabe syntaktisch
 * geprüft und aus einem korrekten Ergebnis ein ParseTree gebildet.
 * Nur ein korrekter ParseTree wird typisiert, um danach
 * die Codeerzeugung darauf aufzurufen.
 * @param sourcefile Übergebener Quelltext, möglichst in der vorgegebenen Sprache
 */
Syntax_Check::Syntax_Check(char* sourcefile){

	scannerpointer = new Scanner(sourcefile);
	actToken = scannerpointer->nextToken();
	failBit = CORRECT;
//    actToken=new  Token(ERROR,1,1);
	tokenType = actToken->getType();
	rootNode = new TreeNode(PROG);
	this -> prog();
	
	if(failBit == CORRECT){
	    // TODO failBit setzen im Check
	    rootNode -> typeCheck(rootNode);
	}
	
	if(failBit == CORRECT){
	   rootNode -> makeCode(rootNode);
	}
	
}

/**
 * Destruktor, gibt Ressourcen wieder frei
 */
Syntax_Check::~Syntax_Check(){

	delete scannerpointer;
	scannerpointer = 0;
}

/**
 * Prog ist Startpunkt für die Syntaxüberprüfung und den Aufbau
 * des ParseTrees. Daraus wird rekursiv nach den Regeln des Skripts -> siehe Skript
 * ein Baum anhand des Quelltextes aufgebaut.
 * Teilt die Syntax in Deklarationen und Anweisungen
 */
void Syntax_Check::prog(){
	rootNode->nodeArray[0] = decls();
	if(failBit == CORRECT){
		rootNode->nodeArray[1] = statements();
	}
}

/**
 * Decls ist Startpunkt für die weitere Überprüfung und Aufbau des
 * Deklarationenteil des Baumes.
 */
TreeNode* Syntax_Check::decls(){
	TreeNode* declsNode=0;
	if(tokenType == IDENTIFIER_INT){
		declsNode = new TreeNode(DECLS);
		declsNode->nodeArray[0] = decl();
		//declsNode -> makeCode(DECLS);
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

/**
 * Decl gibt die Syntax für Überprüfung und Aufbau
 * einer Deklaration vor.
 */
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

/**
 * Array gibt die Syntax und Aufbau von der Array-Deklaration vor.
 */
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

/**
 * Statments ist Startpunkt für Syntax und Aufbau des Anweisungsteil des ParseTree
 */
TreeNode* Syntax_Check::statements(){
	TreeNode* statementsNode=0;
	if(tokenType == STRING || tokenType == IDENTIFIER_WRITE || tokenType == IDENTIFIER_READ
			|| tokenType == OPERATOR_CUREVED_OPEN || tokenType == IDENTIFIER_IF || tokenType == IDENTIFIER_WHILE){
		statementsNode = new TreeNode(STATEMENTS);
		statementsNode->nodeArray[0] = statement();
//			cout  << "done" << endl;
			if(tokenType == OPERATOR_SEMICOL){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				statementsNode->nodeArray[1] = statements();
			}else{
			    failBit = FAIL;
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
			    cout << actToken -> getContainer() -> getValue() << endl;
			}
	}
	else if (tokenType == EOF2 || tokenType == OPERATOR_CURVED_CLOSED){
		statementsNode = new TreeNode(STATEMENTS_EPS);
	}
	else{
		failBit = FAIL;
	    cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        cout << actToken -> getContainer() -> getValue() << endl;
	}
	return statementsNode;
}

/**
 * Statement gibt Syntax und Aufbau von Anweisungen vor
 */
TreeNode* Syntax_Check::statement(){

	TreeNode* statementNode;
	switch(tokenType){


	case STRING:{
		statementNode = new TreeNode(STATEMENT_IDENTIFIER);
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
		statementNode = new TreeNode(STATEMENT_WRITE);
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
		statementNode = new TreeNode(STATEMENT_READ);
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
		statementNode = new TreeNode(STATEMENT_CURVED);
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
		statementNode = new TreeNode(STATEMENT_IF);
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
		statementNode = new TreeNode(STATEMENT_WHILE);
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

/**
 * Exp gibt Syntax und Aufbau von Ausdrücken vor
 */
TreeNode* Syntax_Check::exp(){
	TreeNode* expNode = new TreeNode(EXP);

	expNode->nodeArray[0] = exp2();
	expNode->nodeArray[1] = op_exp();

	return expNode;
}

/**
 * Exp2 gibt die genaue Syntax und Aufbau eines Ausdrucks vor
 */
TreeNode* Syntax_Check::exp2(){
	TreeNode* exp2Node=0;

	if(tokenType == OPERATOR_BR_OPEN){
		exp2Node = new TreeNode(EXP2_BRACK);
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
		exp2Node = new TreeNode(EXP2_IDENTIFIER);
		
	    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
	    exp2Node -> nodeArray[0] = leafe;
	    
//	    cout << "### " << exp2Node -> nodeArray[0] -> getContainer() -> getValue() << endl;
	    
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2Node->nodeArray[1] = index();
	}


	else if(tokenType == NUMBER){
		exp2Node = new TreeNode(EXP2_INT);
	    ParserLeafe* leafe = new ParserLeafe(actToken -> getContainer());
	    exp2Node -> nodeArray[0] = leafe;
	
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}


	else if(tokenType == OPERATOR_MINUS){
		exp2Node = new TreeNode(EXP2_MINUS);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2Node->nodeArray[0] = exp2();
	}


	else if(tokenType == OPERATOR_EXCLAMATION){
		exp2Node = new TreeNode(EXP2_NOT);
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

/**
 * Index gibt Syntax und Aufbau eines Indexes vor
 */
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
			cout << "Fehler nahe " << actToken->getRow() << " , k1" << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
	else if(tokenType == OPERATOR_DEFINITION || tokenType == OPERATOR_BR_CLOSE || isOperator() || OPERATOR_SEMICOL){ // TODO Discuss
		indexNode = new TreeNode(INDEX_EPS);
	}
	else{
		failBit = FAIL;
					cout << "Fehler nahe " << actToken->getRow() << " , k2" << actToken->getCol() << endl;
			        cout << actToken -> getContainer() -> getValue() << endl;
	}

	return indexNode;
}

/**
 * Op_Exp gibt Syntax und Aufbau von der Kombination Operator gefolgt
 * von einem Ausdruck vor.
 */
TreeNode* Syntax_Check::op_exp(){
	TreeNode* op_expNode=0;
	
	if(isOperator()){
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

/**
 * Op gibt Syntax und Baumaufbau von Operatoren vor
 */
TreeNode* Syntax_Check::op(){

	TreeNode* opNode;
	if(tokenType == OPERATOR_PLUS){
		opNode = new TreeNode(OP_ADD);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_MINUS){
		opNode = new TreeNode(OP_SUB);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_STAR){
		opNode = new TreeNode(OP_MUL);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_SLASH){
		opNode = new TreeNode(OP_DIVI);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_LESSTHAN){
		opNode = new TreeNode(OP_LES);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_MORETHAN){
		opNode = new TreeNode(OP_MOR);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_EQUAL){
		opNode = new TreeNode(OP_EQU);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_UNEQUAL){
		opNode = new TreeNode(OP_UNEQ);
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}
	else if(tokenType == OPERATOR_AMPERSAND){
		opNode = new TreeNode(OP_AMPAND);
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

/*
 * Prüft, ob das Token ein Operator ist.
 */
bool Syntax_Check::isOperator(){

    return tokenType == OPERATOR_PLUS || tokenType == OPERATOR_MINUS || tokenType == OPERATOR_STAR ||
			tokenType == OPERATOR_SLASH || tokenType == OPERATOR_LESSTHAN ||
			tokenType == OPERATOR_MORETHAN || tokenType == OPERATOR_EQUAL ||tokenType == OPERATOR_UNEQUAL ||
			tokenType == OPERATOR_AMPERSAND;

}


int main(int argc,char* argv[]){
//    cout << "start parser" << endl;
	Syntax_Check* syncheck = new Syntax_Check(argv[1]);
//	cout << "end parser" << endl;
}




