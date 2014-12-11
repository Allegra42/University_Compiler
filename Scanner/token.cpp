#ifndef __token__
#define __token__

#include "Automat.h"
#include "token.h"
using namespace std;

// Speicherung von dem Container und die dazugehoerige Position im Text


Token::Token(State gState,int row,int col){
    this -> row=row;
    this -> col=col;
    
    this -> myState = gState;
    this -> numValue = 0;
    this -> container = 0;
    
}

state Token::getType(){
    return myState;
}

void Token::setContainer(Container* c){
    this -> container = c;
}

Container* Token::getContainer(){
    return container;
}

void Token::setNumValue(int num){
    this -> numValue = num;
}

int Token::getNumValue(){
    return numValue;
}

int Token::getRow(){
    return row;
}

int Token::getCol(){
    return col;
}

#endif
