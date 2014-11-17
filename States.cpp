#include <iostream>
#include "States.h"

using namespace std;

/**
 * Start- / Initialzustand, verarbeitet das Eingabezeichen 
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach Verarbeitung der Zeichens eingenommen wurde
 */
State States::StateINIT(char c) {
    
    States::counterToLastEndState = 1;
        
        if(c >= '0' && c <= '9')
        {
            return NUMBER;
        }
        
       else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            return STRING;
        }
        
        else if(c == '+' || c == '-' || c == '*' || c == '>' || c == '=' ||
              c == '!' || c == '&' || c == ';' || c == '(' || c == ')' || c == '{' ||
              c == '}' || c == '[' || c == ']')
        {
            return OPERATOR;   
        }
        
        else if (c == '/') {
        	return SLASH;
        }

        else if(c == '<')
        {
            return LESSTHAN;
        }
        
        else if(c == ':')
        {
            return COLON2;
        }

        else if (c == 0) //0 ist in ASCII End of File
        {
        	return EOF;
        }

        else if (c == ' ' || c == 9) // 9 ist in ASCII Tab
        {
        	return WHITESPACE;
        }

        else{
            return EXCEPTION;
        }
    
}

/**
 * Zustand für Zahlen
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateNUMBER(char c) {

    States::counterToLastEndState = 1;
            
        if(c >= '0' && c <= '9') 
        {
            return NUMBER;
        }
        
        else
        {
            return ERROR;
        }
}

/**
 * Zustand für Zeichenketten, Zeichenkette beginnt immer mit einem Buchstaben, 
 * können danach aber beliebig viele Ziffern beinhalten.
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung der Zeichens eingenommen wurde
 */
State States::StateSTRING(char c) {
    
    States::counterToLastEndState = 1;
    
        
        if(((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
        {
            return STRING;
        }
        
        else
        {
            return ERROR;
        }
}

/**
 * Zustand für Operatoren
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateOPERATOR(char c) {

    States::counterToLastEndState = 1;
    return ERROR;
}


/**
 * Zustand für das "kleiner als" Zeichen
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateLESSTHAN(char c) {
    
    States::counterToLastEndState = 1;
    
        if(c == ':') 
        {
            return COLON1;
        }
        
        else
        {
            return ERROR;
        }
}

/**
 * Zustand für ":" Fall 1 (<:>)
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateCOLON1(char c) {
    
    States::counterToLastEndState = 2;
    
        if(c == '>')
        {
            return OPERATOR;
        }
        
        else
        {
            return ERROR;
        }
}

/**
 * Zustand für ":" Fall 2 (:=)
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateCOLON2(char c) {
    
    States::counterToLastEndState = 2;
            
        if(c == '=')
        {
          return OPERATOR;  
        }
        
        else
        {
            return EXCEPTION;
        }
}

/**
 * Zustand für "/" -> daraus kann Operator, Zeilenkommentar, oder Mehrzeilenkommentar werden
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateSLASH(char c) {

	States::counterToLastEndState = 1;

	if(c == '/') {
		return COMMENT1; // Kommentare mit //
	}
	else if (c == '*') {
		return STAR1; // Kommentare mit /*
	}
	else {
		return OPERATOR;
	}
}

State States::StateSTAR1(char c) {

	States::counterToLastEndState = 1;

	if (c == '*') {
		return STAR2;
	}
	else if (c == '\n') {
		States::commentLinesCounter++;
		return COMM;
	}
	else {
		return COMM;
	}
}

State States::StateCOMM(char c) {

	if (c == '*') {
		return STAR2;
	}
	else if (c == '\n') {
		States::commentLinesCounter++;
		return COMM;
	}
	else {
		return COMM;
	}
}

State States::StateSTAR2(char c) {

	if (c == '/') {
		return COMMENT2;
	}
	else {
		return COMM;
	}
}

State States::StateCOMMENT2(char c) {

	States::counterToLastEndState = 1;

	return ERROR;
}

/**
 * Zustand für Zeilenkommentar
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateCOMMENT1(char c) {

	States::counterToLastEndState = 1;

	if (c != '\n') {
		return COMMENT1;
	}
	else {
		return ERROR;
	}
}

/**
 * Zustand für Whitespace bzw. Tabulator
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateWHITESPACE(char c) {
	States::counterToLastEndState = 1;

	if (c == ' ' || c == 9) {
		return WHITESPACE;
	}
	else {
		return ERROR;
	}
}

