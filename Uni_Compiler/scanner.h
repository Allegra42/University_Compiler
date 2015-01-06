#ifndef __scanner__
#define __scanner__

#include "hashmap.h"
#include "buffer.h"
#include "token.h"
#include "container.h"
#include "Automat.h"
#include "genericStorage.h"

#include <string.h>
#include <stdio.h>

using namespace std;

class Scanner{

    public:
            Scanner(char*);
            
            ~Scanner();
            
            // Ermittlung des naechsten Tokens
            Token* nextToken();
            
            // zuruecksetzen der Zeichen
            void rejectChars(int);
            
            // Tokenerstellung
            Token* createNewToken(State,int,int);
            
            Automat* automat;
            
    private:

            Buffer* buffer;

            // interner Zwischenspeicher zum Aufbau des Wortes
//            char internBuffer[9000];
//            char internBufferField[2];
            
            char* internBufferPointer;
            
            // Wortgroesse
            int wordSize;
            
            // max. Wortgroesse
            int maxWordSize;
            
            // Symboltabelle
            HashMap* hashMap;
    
    
            void resetInternBuffer();
            
            void init();
            
            Container* createContainer(char*,State);
            
            void addIntoInternBuffer(char);
            
            char* copyInternBufferIntoBigStorage();
            
            void generateIdentifier(char*,State);
            
};



#endif
