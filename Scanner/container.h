#ifndef __container_h__
#define __container_h__

#include "Automat.h"
using namespace std;

// Speicherung von zusammengehoerigen Text und Typ
class Container{

    public:
            Container(char*,State);
            
            Container(){
            }
            
            char* getValue();
            State getType();
    
    private:
            char* value;
            State state;

};

#endif
