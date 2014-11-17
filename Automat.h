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
	COMMENT1,COMMENT2, STAR1, STAR2, COMM, SLASH, WHITESPACE};
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
    
    int getCommentLines();

    State getLastFinalState();
    
    void reset();
    
private:
    string enumToString(State state);
    State lastFinalState;
    State lastState; //ruf auf dem aktuellen Zustand die Methode um zum nächsten Zustand zu kommen auf
    int stepsBack;
    int commentLines;
};

#endif

