#ifndef __container_h__
#define __container_h__

#include "Automat.h"
using namespace std;

// Speicherung von zusammengehoerigen Text und Typ
class Container{

    public:
            Container(char*,int const i,State);
            ~Container();
            
            
            char* getValue();
            State getType();
            void setNumber(long int);
            long int getNumber();
    
    private:
            char* value;
            State state;
            long int number;

};

#endif
