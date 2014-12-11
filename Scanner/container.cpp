#ifndef __container__
#define __container__

#include "Automat.h"
#include "container.h"
using namespace std;

Container::Container(char* text,State state){
    this -> value = text;
    this -> state = state;
}


char* Container::getValue(){
    
    return value;
    
}

State Container::getType(){
    return state;
}

#endif
