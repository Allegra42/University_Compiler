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
enum state {INIT, ERROR, EOF, NUMBER, STRING, OPERATOR, EXCEPTION, LESSTHAN, COLON1, COLON2,
	COMMENT1,COMMENT2, STAR1, STAR2, COMM, SLASH, WHITESPACE, IDENTIFIER, NEWLINE};
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

    void reject(int colsBack);

    State getLastFinalState();
    
    void reset();
    
private:

    State lastFinalState;
    State lastState; //ruf auf dem aktuellen Zustand die Methode um zum nächsten Zustand zu kommen auf
    int stepsBack;
    int commentLines;
    int newLines;
    int row; //Reihe
    int col; //Spalte

	void calcCol();
};

#endif

