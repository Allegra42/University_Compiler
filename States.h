
#ifndef STATES_H
#define STATES_H


#include <iostream>
#include "Automat.h"

using namespace std;

/**
 * States verwaltet die Verarbeitung des Eingabezeichens im Automaten mit 
 * verschiedenen Zuständen
 */
class States { 

public:
    
    States(){
    	counterToLastEndState = 0;
    	commentLinesCounter = 0;
    	rowCounter = 0;
    	cout << "Object created" << endl ;
    }
    
    ~States(){
       
    }
    
    State StateINIT (char);
    State StateNUMBER (char);
    State StateSTRING (char);
    State StateOPERATOR (char);
    State StateLESSTHAN (char);
    State StateCOLON1 (char);
    State StateCOLON2 (char);
    State StateCOMMENT1 (char);
    State StateCOMMENT2 (char);
    State StateSTAR1 (char);
    State StateSTAR2 (char);
    State StateCOMM (char);
    State StateSLASH (char);
    State StateWHITESPACE (char);
    State StateNEWLINE (char);
    //State StateEOF (char c);
    //State StateERROR (char c);
    //State StateEXCEPTION (char c);
    
    int counterToLastEndState;
    int commentLinesCounter;
    int rowCounter;
    
};

#endif

