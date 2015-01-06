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
//    actToken=new  Token(ERROR,1,1);
	tokenType = actToken->getType();
	this -> prog();
}

Syntax_Check::~Syntax_Check(){

	delete scannerpointer;
	scannerpointer = 0;
}

void Syntax_Check::prog(){
	decls();
	statements();
}

void Syntax_Check::decls(){
	decl();
	if(tokenType == OPERATOR_SEMICOL){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		decls();
	}
}

void Syntax_Check::decl(){
	if(tokenType == NUMBER){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		array();
		if(tokenType == STRING){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}
		else{
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
		 }
	}
	else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
	 }
}

void Syntax_Check::array(){
	if(tokenType == OPERATOR_SQUERED_OPEN){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == NUMBER){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			if(tokenType == OPERATOR_SQUERED_CLOSED){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
			}
			else{
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
            		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else{
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
		 }
	}
}

void Syntax_Check::statements(){
	statement();
	cout  << "done" << endl;
	if(tokenType == OPERATOR_SEMICOL){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		statements();
	}
}

void Syntax_Check::statement(){

	if(tokenType == STRING){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		index();
		if(tokenType == OPERATOR_DEFINITION){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			exp();
		}else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}


	if(tokenType ==  IDENTIFIER_WRITE){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			exp();
			if(tokenType == OPERATOR_BR_CLOSE){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
			}
			else{
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}


	if(tokenType == IDENTIFIER_READ){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			if(tokenType == STRING){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				index();
				if(tokenType == OPERATOR_BR_CLOSE){
					actToken = scannerpointer->nextToken();
					tokenType = actToken->getType();
				}
				else{
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
            		cout << actToken -> getContainer() -> getValue() << endl;
				}
			}
			else {
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}



	if(tokenType == OPERATOR_CUREVED_OPEN){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		statements();
		if(tokenType == OPERATOR_CURVED_CLOSED){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}
		else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}


	if(tokenType == IDENTIFIER_IF){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
			exp();
			if(tokenType == OPERATOR_BR_CLOSE){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				statement();
				if(tokenType == IDENTIFIER_ELSE){
					actToken = scannerpointer->nextToken();
					tokenType = actToken->getType();
					statement();
				}
				else{
					cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
            		cout << actToken -> getContainer() -> getValue() << endl;
				}
			}
			else{
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}



	if(tokenType == IDENTIFIER_WHILE){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		if(tokenType == OPERATOR_BR_OPEN){
		    actToken = scannerpointer->nextToken();
		    tokenType = actToken->getType();
			exp();
			if(tokenType == OPERATOR_BR_CLOSE){
				actToken = scannerpointer->nextToken();
				tokenType = actToken->getType();
				statement();
			}
			else{
				cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
        		cout << actToken -> getContainer() -> getValue() << endl;
			}
		}
		else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
/**	else{
		cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
		cout << actToken -> getContainer() -> getValue() << endl;
	}*/
}

void Syntax_Check::exp(){
	exp2();
	op_exp();
}

void Syntax_Check::exp2(){
	if(tokenType == OPERATOR_BR_OPEN){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp();
		if(tokenType == OPERATOR_BR_CLOSE){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}
		else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}



	if(tokenType == STRING){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		index();
	}


	if(tokenType == NUMBER){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
	}


	if(tokenType == OPERATOR_MINUS){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2();
	}


	if(tokenType == OPERATOR_EXCLAMATION){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp2();
	}

	else{
		cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
		cout << actToken -> getContainer() -> getValue() << endl;
	}
}

void Syntax_Check::index(){
	if(tokenType == OPERATOR_SQUERED_OPEN){
		actToken = scannerpointer->nextToken();
		tokenType = actToken->getType();
		exp();
		if(tokenType == OPERATOR_SQUERED_CLOSED){
			actToken = scannerpointer->nextToken();
			tokenType = actToken->getType();
		}else{
			cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
    		cout << actToken -> getContainer() -> getValue() << endl;
		}
	}
}

void Syntax_Check::op_exp(){
	if(tokenType == OPERATOR_PLUS || tokenType == OPERATOR_MINUS || tokenType == OPERATOR_STAR ||
			tokenType == OPERATOR_SLASH || tokenType == OPERATOR_LESSTHAN ||
			tokenType == OPERATOR_MORETHAN || tokenType == OPERATOR_EQUAL ||tokenType == OPERATOR_UNEQUAL ||
			tokenType == OPERATOR_AMPERSAND){
		op();
		exp();
	}
}

void Syntax_Check::op(){
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
		cout << "Fehler nahe " << actToken->getRow() << " , " << actToken->getCol() << endl;
		cout << actToken -> getContainer() -> getValue() << endl;
	}
}




int main(int argc,char* argv[]){
    cout << "start parser" << endl;
	Syntax_Check* syncheck = new Syntax_Check(argv[1]);
	cout << "end parser" << endl;
}




