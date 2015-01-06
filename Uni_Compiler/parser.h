#ifndef __parser_h__
#define __parser_h__

#include "scanner.h"
using namespace std;

class Parser{
    
    public:
        Parser(char*);
        ~Parser();
        
    private:
        Scanner* scannerPointer;
    
};


#endif
