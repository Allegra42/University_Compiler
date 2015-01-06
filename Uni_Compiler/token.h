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
            int getCol();
            int getRow();
    
    private:
            Container* container;
            int row; // Zeile
            int col; // Spalte bzw. Zeichen
            

};

#endif
