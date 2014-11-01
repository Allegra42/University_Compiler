#include "Automat.h"
#include "States.h"
#include <iostream>
#include <string.h>

using namespace std;

/**
 * Initialisiert den Automat mit dem Startzustand
 */
Automat::Automat(){
    states = new States();
    lastState = INIT;
    lastFinalState = INIT;

}


/**
 * Methode, die der Scanner aufruft, um zu Erfahren was für ein Typ das Zeichen hat
 * @param c Eingabezeichen vom Scanner
 * @return Zustand in den nach Verarbeitung des Zeichens gewechselt wird
 */
State Automat::put(char c) {
    State lastFinal = Automat::lastFinalState;
    State lastNormal = Automat::lastState;
    
    // Da mehrere Zeichen hintereinander in den Automaten kommen,
    // ist die Verarbeitung abhängig vom aktuellen Zustand


    if (Automat::lastState == INIT)
    {
            lastNormal =states->StateINIT(c);
    }
        
    if (Automat::lastState == NUMBER)
    {
            lastNormal = states->StateNUMBER(c);
            lastFinal = lastNormal;
    }
        
    if (Automat::lastState == STRING)
    {
            lastNormal = states->StateSTRING(c);
            lastFinal = lastNormal;
    }
        
    if (Automat::lastState == OPERATOR)
    {
            lastNormal = states->StateOPERATOR(c);
    }
        
    if (Automat::lastState == LESSTHAN)
    {
            lastNormal = states->StateLESSTHAN(c);
    }
        
    if (Automat::lastState == COLON1)
    {
            lastNormal = states->StateCOLON1(c);
            lastFinal = LESSTHAN;
    }
        
    if (Automat::lastState == COLON2)
    {
            lastNormal = states->StateCOLON2(c);
    }
        
    

    Automat::lastFinalState = lastFinal;
    Automat::lastState = lastNormal;

    string stringlastnormal = enumToString(lastState);
    string stringlastfinal = enumToString(lastFinalState);

    cout << "lastState : " << stringlastnormal << endl;
    cout << "lastFinalState : " << stringlastfinal << endl;
    
    return lastNormal;
}

/**
 * Wird vom Scanner aufgerufen um zu erfahren wie viele Schritte er evtl. 
 * zurück gehen muss, um den Schluss der letzten Tokens zu finden.
 * @return Schritte bis zum Ende des letzten Tokens
 */
int Automat::getStepsToLastFinalState() {
    
    return states->counterToLastEndState;
}

/**
 * Wird vom Scanner aufgerufen um zu erfahren von welchem Typ das gerade zu 
 * erstellende Token sein soll
 * @return Typ / Zustand des letzten finalen Zustands des Automaten
 */
State Automat::getLastFinalState() {
    
    return Automat::lastFinalState;
}

/**
 * Wird vom Scanner aufgerufen um nach Bildung eines Tokens den Automat wieder 
 * auf den Startzustand zu setzen
 */
void Automat::reset() {
    
    Automat::lastState = INIT;   
    Automat::lastFinalState = INIT;
    cout << "cleared Automat" << endl;
}

string Automat::enumToString (State state) {
	if (state == INIT){
		return "INIT";
	}
	if (state == ERROR){
		return "ERROR";
	}
	if (state == EOF){
		return "EOF";
	}
	if (state == NUMBER){
		return "NUMBER";
	}
	if (state == OPERATOR){
		return "OPERATOR";
	}
	if (state == EXCEPTION){
		return "EXCEPTION";
	}
	if (state == LESSTHAN){
		return "LESSTHAN";
	}
	if (state == COLON1){
		return "COLON1";
	}
	if (state == COLON2){
		return "COLON2";
	}
	else{
		return "NOTHING";
	}
}


int main() {
	Automat *automat = new Automat();
	automat->put('9');
	automat->put('+');
	automat->reset();

}

