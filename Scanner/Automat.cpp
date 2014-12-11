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
    stepsBack = 0;
    commentLines = 0;
    newLines = 0;
    row = 1;
    col = 0;
    latest=0;
    
    // TODO delete
    temp=0;

}



/**
 * Methode, die der Scanner aufruft, um zu Erfahren was für ein Typ das Zeichen hat
 * @param c Eingabezeichen vom Scanner
 * @return Zustand in den nach Verarbeitung des Zeichens gewechselt wird
 */
State Automat::put(char c) {
	col++;
	
	// TODO delete
	/*if(c=='\n'){
	    temp++;
	    cout << temp << endl;
	}*/
	
    State lastNormal = Automat::lastState;
    State lastFinal = lastNormal;
    
    // Da mehrere Zeichen hintereinander in den Automaten kommen,
    // ist die Verarbeitung abhängig vom aktuellen Zustand


    if (Automat::lastState == INIT)
    {
            latest=col;
            
            lastNormal = states->StateINIT(c);
            if (lastNormal == EOF2){
            	lastFinal = EOF2;
            }
            if (lastNormal == EXCEPTION){
            	lastFinal = EXCEPTION;
            }

            stepsBack = states->counterToLastEndState;

    }
        
    if (Automat::lastState == NUMBER)
    {
            lastNormal = states->StateNUMBER(c);
            stepsBack = states->counterToLastEndState;
    }
        
    if (Automat::lastState == STRING)
    {
            lastNormal = states->StateSTRING(c);
            stepsBack = states->counterToLastEndState;
    }
        
    if (Automat::lastState == OPERATOR)
    {
            lastNormal = states->StateOPERATOR(c);
            stepsBack = states->counterToLastEndState;
    }
        
    if (Automat::lastState == LESSTHAN)
    {
            lastNormal = states->StateLESSTHAN(c);
            
            if(lastNormal == ERROR){
                lastFinal=OPERATOR;
            }
            
            stepsBack = states->counterToLastEndState;
    }
        
    if (Automat::lastState == COLON1)
    {
            lastNormal = states->StateCOLON1(c);
            if (lastNormal == OPERATOR){
            	lastFinal = OPERATOR;
            	stepsBack = 1;
            }
            else {
            	lastFinal = LESSTHAN;
            	stepsBack = states->counterToLastEndState;
            }

    }

        
    if (Automat::lastState == COLON2)
    {
            lastNormal = states->StateCOLON2(c);
            if (lastNormal == OPERATOR) {
            	stepsBack = states->counterToLastEndState;
            	lastFinal = OPERATOR;
            }
            else {
            	lastFinal = EXCEPTION;
            	stepsBack = states->counterToLastEndState;
            }

    }

    if (Automat::lastState == SLASH)
    {
    	stepsBack = states->counterToLastEndState;
    	lastNormal = states->StateSLASH(c);
    	if (lastNormal == ERROR){
    		lastFinal = OPERATOR;
    	}
    
    }

    if (Automat::lastState == COMMENT1) {

    	stepsBack = states->counterToLastEndState;
    	lastNormal = states->StateCOMMENT1(c);

    }

    if (Automat::lastState == STAR1) {

    	commentLines = states->commentLinesCounter;
    	stepsBack = states->counterToLastEndState;
    	lastNormal = states->StateSTAR1(c);

    }

    if (Automat::lastState == COMM || lastState == COMM_NEWLINE) {

    	commentLines = states->commentLinesCounter;
    	lastNormal = states->StateCOMM(c);
    	
    	if(lastState==COMM_NEWLINE){
    	
    	    createNewLine();
    	    cout << "COMM_NEWLINE" << endl;
    	
    	}
    	
    }

    if (Automat::lastState == STAR2) {

    	lastNormal = states->StateSTAR2(c);

    }

    if (Automat::lastState == COMMENT2) {

    	stepsBack = states->counterToLastEndState;
    	lastNormal = states->StateCOMMENT2(c);

    }

    if (Automat::lastState == WHITESPACE) {

    	stepsBack = states->counterToLastEndState;
    	lastNormal = states->StateWHITESPACE(c);
    //	Automat::calcCol();
    }

    if (Automat::lastState == NEWLINE) {

       newLines++;
       stepsBack = states->counterToLastEndState;
       lastNormal = states->StateNEWLINE(c);
       
       //cout << "#*#" << endl;
       this -> createNewLine();
       
      // Automat::calcCol();

    }
    /*
    if (Automat::lastState == NEWLINE) {
    	newLines = states->commentLinesCounter;
    	stepsBack = states->counterToLastEndState;
    	lastNormal = states->StateNEWLINE(c);
    }*/

    if (Automat::lastState == ERROR)
    {
        stepsBack = states->counterToLastEndState;
		//Automat::calcCol();
    }

//    Automat::calcCol();
        
    Automat::lastFinalState = lastFinal;
    Automat::lastState = lastNormal;

    string stringlastnormal = enumToString(lastState);
    string stringlastfinal = enumToString(lastFinalState);

//    cout << "lastState : " << stringlastnormal << endl;

    return lastNormal;
}


void Automat::createNewLine(){

    row++;
    col=1;

}


/**
 * Wird vom Scanner aufgerufen um zu erfahren wie viele Schritte er evtl. 
 * zurück gehen muss, um den Schluss der letzten Tokens zu finden.
 * @return Schritte bis zum Ende des letzten Tokens
 */
int Automat::getStepsToLastFinalState() {
    
//	cout << "Schritte zurück zum Ende des letzten Tokens : " << stepsBack << endl;
    col-=stepsBack;
    return stepsBack;
}

int Automat::getCommentLines() {

//	cout << "Anzahl Zeilen des Mehrzeilenkommentars : " << commentLines << endl;
	return commentLines;
}

int Automat::getNewLines() {
//	cout << "Anzahl Newlines: " << newLines << endl;
	return newLines;
}

int Automat::getCol() {
//	cout << "Spalte: " << col << endl;
	return latest;
}

int Automat::getRow() {
//	cout << "Zeile: " << row << endl;
	return row;
}

/**
 * Wird vom Scanner aufgerufen um zu erfahren von welchem Typ das gerade zu 
 * erstellende Token sein soll
 * @return Typ / Zustand des letzten finalen Zustands des Automaten
 */
State Automat::getLastFinalState() {
    string lastfinal = enumToString(lastFinalState);
//    cout << "Letztes Token ist vom Typ : " << lastfinal << endl;
    return Automat::lastFinalState;
}

/**
 * Wird vom Scanner aufgerufen um nach Bildung eines Tokens den Automat wieder 
 * auf den Startzustand zu setzen
 */
void Automat::reset() {
    Automat::lastState = INIT;   
    Automat::lastFinalState = INIT;
    Automat::commentLines = 0;
    Automat::newLines = 0;
    latest=0;
//    cout << "cleared Automat" << endl;
}

string Automat::enumToString (State state) {
	if (state == INIT){
		return "INIT";
	}
	if (state == ERROR){
		return "ERROR";
	}
	if (state == EOF2){
		return "EOF2";
	}
	if (state == NUMBER){
		return "NUMBER";
	}
	if (state == STRING){
		return "STRING";
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

	if (state == COMMENT1){
		return "COMMENT1";
	}

	if (state == COMMENT2){
		return "COMMNENT2";
	}

	if (state == STAR1){
		return "STAR1";
	}

	if (state == COMM){
		return "COMM";
	}

	if (state == STAR2){
		return "STAR2";
	}

	if (state == SLASH){
		return "SLASH";
	}

	if (state == WHITESPACE){
		return "WHITESPACE";
	}

	if (state == NEWLINE){
		return "NEWLINE";
	}

	if (state == IDENTIFIER) {
		return "IDENTIFIER";
	}

	else{
		return "NOTHING";
	}
}


/*int main() {
	Automat *automat = new Automat();

	automat->getRow();
	automat->getCol();
	automat->put('a');
	automat->put('b');
	automat->put('9');
	automat->put('+');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('+');
	automat->put('a');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put(':');
	//automat->put('=');
	automat->put(0);
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('<');
	automat->put(':');
	automat->put('>');
	automat->put('j');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('<');
	automat->put(':');
	automat->put('=');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put(':');
	automat->put('+');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('\0');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('/');
	automat->put('/');
	automat->put('a');
	automat->put('f');
	automat->put('7');
	automat->put('+');
	automat->put('\n');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('/');
	automat->put('*');
	automat->put('a');
	automat->put('f');
	automat->put('7');
	automat->put('*');
	automat->put('/');
	automat->put('u');
	automat->getStepsToLastFinalState();
	automat->getCommentLines();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('/');
	automat->put('*');
	automat->put('\n');
	automat->put('a');
	automat->put('\n');
	automat->put('*');
	automat->put('/');
	automat->put('h');
	automat->getStepsToLastFinalState();
	automat->getCommentLines();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put(' ');
	automat->put(' ');
	automat->put(9);
	automat->put('p');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('/');
	automat->put('4');
	//automat->put('5');
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
	automat->getCol();
	automat->put('<');
	automat->put(' ');
	//automat->put('o');
	automat->getNewLines();
	automat->getStepsToLastFinalState();
	automat->getLastFinalState();

	automat->reset();
	cout << endl;

	automat->getRow();
		automat->getCol();

}*/

//TODO
//
// Zeilen und Spaltenzähler -> mit reject-funktion (schritte zurück)
