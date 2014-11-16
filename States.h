/* 
 * File:   StateInterface.h
 * Author: anna
 *
 * Created on 22. Oktober 2014, 15:39
 */
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
    State StateSLASH (char);
    State StateCOMMENT21 (char);
    State StateWHITESPACE (char);
    //State StateEOF (char c);
    //State StateERROR (char c);
    //State StateEXCEPTION (char c);
    
    int counterToLastEndState;
    
};

#endif

