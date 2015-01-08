#ifndef __token__
#define __token__

#include "Automat.h"
#include "token.h"
using namespace std;

// Erstellung eines Tokens mit dem Typ und der Position im Quelltext
Token::Token(State gState,int row,int col){
    this -> row=row;
    this -> col=col;
    this -> container = 0;
    
}

// gibt den aktuellen Tokentyp zurueck
state Token::getType(){
    return container->getType();
}

// setzt den Container des Tokens
void Token::setContainer(Container* c){
    this -> container = c;
}

// gibt den Container des Tokens zurück
Container* Token::getContainer(){
    return container;
}

// gibt die Zeile des Tokens zurück
int Token::getRow(){
    return row;
}

// gibt die Spalte des Tokens zurück
int Token::getCol(){
    return col;
}

#endif
