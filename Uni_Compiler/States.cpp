#include <iostream>
#include "States.h"

using namespace std;


typedef enum state State;
/**
 * Start- / Initialzustand, verarbeitet das Eingabezeichen 
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach Verarbeitung der Zeichens eingenommen wurde
 */
State States::StateINIT(char c) {
    
    States::counterToLastEndState = 1;
    //States::rowCounter = 0;
        
        if(c >= '0' && c <= '9')
        {
            return NUMBER;
        }
        
       else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            return STRING;
        }
        
        else if(c == '+')
        {
        	return OPERATOR_PLUS;
        }

        else if (c == '-')
        {
            return OPERATOR_MINUS;
        }

        else if (c == '*')
        {
            return OPERATOR_STAR;
        }

        else if (c == '>')
        {
            return OPERATOR_MORETHAN;
        }

        else if (c == '=')      
        {
            return OPERATOR_EQUAL;
        }

        else if (c == '!')
        {
            return OPERATOR_EXCLAMATION;
        }

        else if (c == '&')
        {
            return OPERATOR_AMPERSAND;
        }

        else if (c == ';')
        {       
            return OPERATOR_SEMICOL;
        }

        else if (c == '(')
        {
            return OPERATOR_BR_OPEN;
        }

        else if (c == ')')
        {
            return OPERATOR_BR_CLOSE;
        }

        else if (c == '{')
        {
            return OPERATOR_CUREVED_OPEN;
        }

        else if (c == '}')
        {
            return OPERATOR_CURVED_CLOSED;
        }
        
        else if (c == '[')
        {
            return OPERATOR_SQUERED_OPEN;
        }

        else if (c == ']')
        {
            return OPERATOR_SQUERED_CLOSED;
        }



        else if (c == '/') {
        	return SLASH;
        }

        else if(c == '<')
        {
            return OPERATOR_LESSTHAN;
        }
        
        else if(c == ':')
        {
            return COLON2;
        }

        else if (c == 0) //0 ist in ASCII End of File
        {
        	return EOF2;
        }

        else if (c == ' ' || c == 9 || c == '\r') // 9 ist in ASCII Tab
        {
        	return WHITESPACE;
        }
        else if (c == '\n')
        {
        	States::rowCounter++;
        	return NEWLINE;
        }

        else{
            States::counterToLastEndState=0;
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
   // States::rowCounter = 0;
            
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
    //States::rowCounter = 0;
    
        
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
    //States::rowCounter = 0;
    return ERROR;
}


/**
 * Zustand für das "kleiner als" Zeichen
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateLESSTHAN(char c) {
    
    States::counterToLastEndState = 1;
    //States::rowCounter = 0;
    
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
    //States::rowCounter = 0;
    
        if(c == '>')
        {
            return OPERATOR_UNEQUAL;
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
    
    //States::rowCounter = 0;
            
        if(c == '=')
        {
          States::counterToLastEndState = 0;
          return OPERATOR_DEFINITION;  
        }
        
        else
        {
        	States::counterToLastEndState = 1;
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
	//States::rowCounter = 0;

	if(c == '/') {
		return COMMENT1; // Kommentare mit //
	}
	else if (c == '*') {
		return STAR1; // Kommentare mit /*
	}
	else {
		return ERROR;
	}
}

/**
 * Zustand für /"*", also den ersten Stern des Mehrzeilenkommentars.
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateSTAR1(char c) {

	States::counterToLastEndState = 1;
	//States::rowCounter = 0;

	if (c == '*') {
		return STAR2;
	}else if(!c){
//	    cout << "eof" << endl;
	    States::counterToLastEndState = 1;
	    return EXCEPTION;
	}
	
	else if (c == '\n') {
		States::commentLinesCounter++;
		States::rowCounter++;
		return COMM;
	}
	else {
		return COMM;
	}
}

/**
 * Zustand für alles was im Mehrzeilenkommentar geschrieben ist. Auch Sterne dürfen hier wieder auftreten
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateCOMM(char c) {

	States::rowCounter = 0;

	if (c == '*') {
		return STAR2;
	}else if(!c){
//	    cout << "eof" << endl;
	    States::counterToLastEndState = 1;
	    return EXCEPTION;
	}
	else if (c == '\n') {
		States::commentLinesCounter++;
		States::rowCounter = 1;
		return COMM_NEWLINE;
	}
	else {
		return COMM;
	}
}

/**
 * Zustand für den möglichen zweiten Stern des Mehrzeilenkommentars. Kommt nur in den Zustand COMMENT2,
 * wenn darauf ein "/" folgt. Sonst wird wieder in dem COMM Zustand gewechselt.
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateSTAR2(char c) {

	//States::rowCounter = 0;


	if (c == '/') {
		return COMMENT2;
	}else if(c == '*'){
	    return STAR2;
	}
	else {
		return COMM;
	}
}

/**
 * Zustand für das Ende des Mehrzeilenkommentars
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateCOMMENT2(char c) {

	States::counterToLastEndState = 1;
	//States::rowCounter = 0;
	return ERROR;
}

/**
 * Zustand für Zeilenkommentar
 * @param c Eingabezeichen vom Scanner
 * @return Zustand, der nach der Verarbeitung des Zeichens eingenommen wurde
 */
State States::StateCOMMENT1(char c) {

	States::counterToLastEndState = 1;
	//States::rowCounter = 0;

	if (c != '\n') {
		return COMMENT1;
	}
	else {
		States::rowCounter++;
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
	//States::rowCounter = 0;

	if (c == ' ' || c == 9 || c == '\r') {
		return WHITESPACE;
	}
	else {
		return ERROR;
	}
}

// Zustand für Zeilenumbrüche
// erhöht den internen Zeilenzähler
State States::StateNEWLINE(char c) {
	States::counterToLastEndState = 1;
	//States::rowCounter = 0;

	if (c == '\n') {
		States::rowCounter++;
		return NEWLINE;
	}
	else {
		return ERROR;
	}
}

