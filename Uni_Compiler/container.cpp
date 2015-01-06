#ifndef __container__
#define __container__

#include "Automat.h"
#include "container.h"
using namespace std;

// erstellen eines Kontainers für den Text und den Zustand des Tokens
// jedes Token, dass keine Nummer oder Kommentar ist, erhält ein solches
Container::Container(char* text,int wordSize,State state){
    this -> state = state;
    this -> value = new char[wordSize];
    
    for(int i=0;i<wordSize;i++){
        value[i]=text[i];
    }
}

// freigeben des Speichers
Container::~Container(){
    delete[] value;
    
}

// gibt den Wert des Tokens zurück
char* Container::getValue(){
    
    return value;
    
}

// gibt den Typ des Tokens zurück
State Container::getType(){
    return state;
}

// setzen eines Zahlenwertes fuer den Container
void Container::setNumber(long int num){
    this -> number = num;
}

// erhalten des Zahlenwertes fuer den Container
long int Container::getNumber(){
    return number;
}

#endif
