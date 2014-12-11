#ifndef __token_h__
#define __token_h__

#include "container.h"
using namespace std;

class Token{

    public:
            Token(State,int,int);
            
            Token(){
            }
            
            ~Token(){
                delete[] container;
            }
            
            state getType();
            void setContainer(Container*);
            Container* getContainer();
            void setNumValue(int);
            int getNumValue();
            int getCol();
            int getRow();
    
    private:
            Container* container;
            state myState;
            int row; // Zeile
            int col; // Spalte bzw. Zeichen
            
            int numValue; // numerischer Wert

};

#endif
