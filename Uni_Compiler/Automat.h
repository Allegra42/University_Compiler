/* 
 * File:   Automat.h
 * Author: anna
 *
 * Created on 22. Oktober 2014, 13:12
 */
#ifndef AUTOMAT_H
#define AUTOMAT_H

#include <iostream>
//#include "States.h"

using namespace std; 

/*
 * Typdefinition für den Rückgabetyp an den Scanner
 * -> Zustande des Automaten
 */
enum state {INIT, ERROR, EOF2, NUMBER, STRING, OPERATOR_PLUS,OPERATOR_MINUS, OPERATOR_SLASH,
    OPERATOR_STAR, OPERATOR_LESSTHAN, OPERATOR_MORETHAN, OPERATOR_EQUAL, OPERATOR_DEFINITION,
    OPERATOR_UNEQUAL, OPERATOR_EXCLAMATION, OPERATOR_AMPERSAND, OPERATOR_SEMICOL, OPERATOR_BR_OPEN,
    OPERATOR_BR_CLOSE, OPERATOR_CUREVED_OPEN, OPERATOR_CURVED_CLOSED, OPERATOR_SQUERED_OPEN,
    OPERATOR_SQUERED_CLOSED, EXCEPTION, COLON1, COLON2,
    COMMENT1,COMMENT2, STAR1, STAR2, COMM, SLASH, WHITESPACE,IDENTIFIER, IDENTIFIER_IF,IDENTIFIER_WHILE,
    IDENTIFIER_READ, IDENTIFIER_WRITE, IDENTIFIER_INT, IDENTIFIER_ELSE, NEWLINE,COMM_NEWLINE,OPERATOR};
typedef enum state State;

class States;

/**
 * Schnittstelle für den Scanner, der die Methoden aufruft
 */
class Automat {
    
public:
    //friend class States;
    
    States *states;
    
    Automat();
       
 
    ~Automat(){
        //TODO
    }
    State put (char);
   
    int getStepsToLastFinalState();
    
    string enumToString(State state);

    int getCommentLines();

    int getNewLines();

    int getRow();

    int getCol();

    State getLastFinalState();
    
    void reset();
    
    void createNewLine();
    
private:

    State lastFinalState;
    State lastState; //ruf auf dem aktuellen Zustand die Methode um zum nächsten Zustand zu kommen auf
    int stepsBack;
    int commentLines;
    int newLines;
    int row; //Reihe
    int col; //Spalte
    int latest;
    int temp;

};

#endif

