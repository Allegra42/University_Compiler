
#include "scanner.h"

#include <errno.h>
#include <stdlib.h> 
#include <iostream>
using namespace std;

/*
// main-Methode zum Testen
int main(int argc, char* argv[]){

    if (argc < 2) {
		cout << "fail" <<endl;
		cout << "to less param" << endl;
		return EXIT_FAILURE;
	}

    Scanner* scanner=new Scanner(argv[1]);

    Token* token;
    
    Container* container;
    
    do{
        token=scanner -> nextToken();
        
//        cout << "new token!" << endl;
        
        container = token -> getContainer();
        cout << "TOKEN: "<< scanner->automat -> enumToString( container->getType() ) << ":" << token -> getRow() << "/" << token -> getCol()<< endl;
//        cout << "_.-:" << container->getType()<<endl;
        
//        cout <<"t"<< token->getType() <<":" << endl;
        
        if(container -> getType()==NUMBER){
            cout << "# " << token -> getContainer() -> getNumber();
        }else{
            cout << token -> getContainer() -> getValue();
        }
        cout << endl << endl;    
//        i--;
    }while(container -> getType()!=EOF2 &&1);
    
    cout << "END of input" << endl << endl;
    
}*/



// erstelle neue token, abhaening von den Zeichen und dem Typ, die der Buffer und der Automat ermittelt
Token* Scanner::nextToken(){
    
    char c;
    State state;
    Token* tokenReference=0;
    int backSteps=0;
    wordSize=0;
    
    while(tokenReference==0){

        c = buffer -> nextChar();
        state = automat -> put(c);
        
        
        if(state!=ERROR){
            this -> addIntoInternBuffer(c);
        }

//        cout << internBufferPointer << "  |  " << automat -> enumToString(state) << endl;
        
        if(state == ERROR || state == EOF2 || state == EXCEPTION){
        
            state = automat -> getLastFinalState();
            backSteps = automat -> getStepsToLastFinalState();
            
//            cout << "state:"<<automat->enumToString(state)<<endl;
            
            if(state != WHITESPACE && state != NEWLINE && state != COMMENT1 && state != COMMENT2){
                
                wordSize-=(backSteps-1);
                
                if(state == EXCEPTION){
                    wordSize--;
                }
                
                addIntoInternBuffer('\0');
                
//                cout << "wordSize:"<<wordSize << endl;
                
                Container* containerReference = this -> createContainer(internBufferPointer,state);
                
                int row=automat -> getRow();
                int col=automat -> getCol();
                tokenReference = createNewToken(state,row,col);
                tokenReference -> setContainer(containerReference);
                
                if(state == NUMBER){
                    
                    char* t;
                    char* begin = containerReference -> getValue();
                    long int test;
                    errno=0;
                    test=strtol(begin,&t,10);
                            
                    if (errno == ERANGE){
                        cout << "#WARNING: "<< begin << " is out of range of long int"<< endl;
                    }
                            
                    containerReference -> setNumber(test);
                    
                }
            
            }    
        
            this->rejectChars(backSteps);
            
        }
        
    
    }
    
    cout << "TOKEN: "<< automat -> enumToString( tokenReference-> getContainer() ->getType() ) << ":" << tokenReference -> getRow() << "/" << tokenReference -> getCol()<< endl;
    
    return tokenReference;

}

// zuruecksetzen der Zeichen intern und im Buffer
void Scanner::rejectChars(int amount){
    buffer->resetBy(amount);
    resetInternBuffer();
    automat -> reset();
}

// Tokenerstellung mit ermittelten Daten
Token* Scanner::createNewToken(State state,int row,int col){
    return new Token(state,row,col);
}

// Container Erstellung, um die Zeichen abzulegen
Container* Scanner::createContainer(char* word,State state){

    Container* containerReference = hashMap -> get(word);
    
    if(!containerReference){
        
        containerReference = new Container(word,wordSize,state);
        hashMap -> add(containerReference);
        
    }
    
    return containerReference;
}

// Konstruktor initialisiert den Scanner
Scanner::Scanner(char* filepath){
    cout << "INIT" << endl;
    
    automat=new Automat();
    buffer=new Buffer(filepath);

    this -> init();
    
    cout << "END INIT" << endl;
    
//    cout << automat -> enumToString(hashMap -> get("if")->getType()) << endl;
}

Scanner::~Scanner(){
    delete automat;
    delete buffer;
    
    delete internBufferPointer;
    delete hashMap;
    internBufferPointer=0;

}


// auf Ausgangswerte zuruecksetzen
void Scanner::resetInternBuffer(){
    wordSize = 0;
}

// Daten initialisieren
void Scanner::init(){
    
    maxWordSize=512;
    char* buffer=new char[maxWordSize];
    internBufferPointer=buffer;
    
    hashMap = new HashMap();
    
    wordSize=0;
    
    this -> generateIdentifier("if\0",IDENTIFIER_IF);
    this -> generateIdentifier("IF\0",IDENTIFIER_IF);
    this -> generateIdentifier("else\0",IDENTIFIER_ELSE);
    this -> generateIdentifier("ELSE\0",IDENTIFIER_ELSE);
    this -> generateIdentifier("while\0",IDENTIFIER_WHILE);
    this -> generateIdentifier("WHILE\0",IDENTIFIER_WHILE);
    this -> generateIdentifier("write\0",IDENTIFIER_WRITE);
//    this -> generateIdentifier("WRITE\0",IDENTIFIER_WRITE);
    this -> generateIdentifier("read\0",IDENTIFIER_READ);
//    this -> generateIdentifier("READ\0",IDENTIFIER_READ);
    this -> generateIdentifier("int\0",IDENTIFIER_INT);

}


// Erstellung von Schluesselwoertern samt dazugehoerigen Kontainer
// Speicherung in den angebotenen Speicherfeldern
void Scanner::generateIdentifier(char* ident,State state){
    
    wordSize=0;
    char c;
    
    do{
        c = *ident;
        ident++;
        this -> addIntoInternBuffer(c);
    }while(c);
    
    this -> createContainer(internBufferPointer,state);

}

// das Zeichen in den internen Speichern einfuegen
void Scanner::addIntoInternBuffer(char c){

    if(maxWordSize == wordSize){
        
        maxWordSize *= 2;
        
        char* temp = new char[maxWordSize];
        
        memcpy(temp,internBufferPointer,wordSize);
        
        delete[] internBufferPointer;
        internBufferPointer = temp;
        
    }
    
    internBufferPointer[wordSize]=c; 
    wordSize++;
}



