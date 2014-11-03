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
        
        else if(c == '+' || c == '-' || c == '/' || c == '*' || c == '>' || c == '=' ||
              c == '!' || c == '&' || c == ';' || c == '(' || c == ')' || c == '{' ||
              c == '}' || c == '[' || c == ']')
        {
            return OPERATOR;   
        }
        
        else if(c == '<')
        {
            return LESSTHAN;
        }
        
        else if(c == ':')
        {
            return COLON2;
        }

        //TODO Exception hier?


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


