#include "Automat.h"
#include "States.h"

using namespace std;

/**
 * Initialisiert den Automat mit dem Startzustand
 */
Automat::Automat(){
    states = new States();
    this->init();
    
}

void Automat::init() {
    lastState = INIT;
    
}

/**
 * Methode, die der Scanner aufruft, um zu Erfahren was für ein Typ das Zeichen hat
 * @param c Eingabezeichen vom Scanner
 * @return Zustand in den nach Verarbeitung des Zeichens gewechselt wird
 */
State Automat::put(char c) {
    State lastFinal = Automat::lastFinalState;
    State lastNormal;
    
    // Da mehrere Zeichen hintereinander in den Automaten kommen,
    // ist die Verarbeitung abhängig vom aktuellen Zustand
    switch(Automat::lastState) {
        case(INIT):
        {
            lastNormal =states->StateINIT(c);
        }
        
        case (NUMBER):
        {
            lastNormal = states->StateNUMBER(c);
            lastFinal = lastNormal;
        }
        
        case(STRING):
        {
            lastNormal = states->StateSTRING(c);
            lastFinal = lastNormal;
        }
        
        case(OPERATOR):
        {
            lastNormal = states->StateOPERATOR(c);
        }
        
        case (LESSTHAN):
        {
            lastNormal = states->StateLESSTHAN(c);
        }
        
        case (COLON1):
        {
            lastNormal = states->StateCOLON1(c);
            lastFinal = LESSTHAN;
        }
        
        case (COLON2):
        {
            lastNormal = states->StateCOLON2(c);
        }
        
    }
    
    Automat::lastFinalState = lastFinal;
    Automat::lastState = lastNormal;
    
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
}
