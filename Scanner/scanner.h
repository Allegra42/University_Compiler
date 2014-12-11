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

			Automat * automat;
			Buffer * buffer;

            Scanner();
            
            ~Scanner();
            
            // Ermittlung des naechsten Tokens
            Token* nextToken();
            
            // zuruecksetzen der Zeichen
            void rejectChars(int);
            
            // Tokenerstellung
            Token* createNewToken(State,int,int);
            
    private:

            // interner Zwischenspeicher zum Aufbau des Wortes
            char internBuffer[2000];
//            char internBufferField[2];
            
            // Wortgroesse
            int wordSize;
            
            // Schritte zurueck zum letzten Entzustand
            int backSteps;

            // Zeiger auf aktuellstes Speicherfeld fuer Zeichenketten
            char* bigArrayPointer;
            // Zeicher auf Anfang des aktuellsten Speicherfelds fuer Zeichenketten
            char* startBigArray;
            // Speicher aller Worte
            LinkedList< GenericStorage<char> > wordList;
            
            
            // Zeiger auf aktuellstes Speicherfeld fuer Container
            Container* containerBlockPointer;
            // Zeiger auf Anfang des aktuellsten Speicherfelds fuer Container
            Container* startContainerBlock;
            // Speicher aller Container
            LinkedList<Container*> containerList;

            
            HashMap* hashMap;
    
            void resetInternBuffer();
            
            void init();
            
            Container* createContainer(char*,State);
            
            void addIntoInternBuffer(char);
            
            void copyInternBufferIntoBigStorage();
            
            void generateIdentifier(char*);
            
            void createWordSpace();
            
            void createContainerSpace();
	    
	    char* sourceFile;

};



#endif
