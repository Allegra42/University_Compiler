//TODO erweitere Speicherverwaltung erneut testen

#include "scanner.h"

#include <stdlib.h> 
#include <iostream>
using namespace std;







// erstelle neue token, abhaening von den Zeichen und dem Typ, die der Buffer und der Automat ermittelt
Token* Scanner::nextToken(){

    // neuen Speicher fuer interne Variablen  anfordern
    // interne Daten zuruecksetzen
    char c;
    Token* token=0;
    backSteps=0;
    cout << "fehler ist nicht im automat" << endl;
    automat -> reset();
    cout << "fehler ist nicht im internen buffer"<<endl;
    this -> resetInternBuffer();
    
    
    while(!token){ // wenn ein Token existiert, ist der daraufweisende Zeiger gesetzt, d.h. ungleich 0 und die Schleife wird verlassen
        cout << " wir versuchen ein zeichen vom buffer zu bekommen" << endl;
        c = buffer->nextChar();
        
        cout << "--------->"<<c<<"<---------"<<endl;
        
        
        state state = automat -> put(c);
        
        if(state!=ERROR){
            this -> addIntoInternBuffer(c);
        }
        
        // Tokenerstellung erst nachdem ein Fehler, eine Ausnahme oder das Dateiende gelesen wurden
        if(state==ERROR || state==EXCEPTION || state==EOF2){
            backSteps=automat->getStepsToLastFinalState();
            
//            cout << "backsteps"<< backSteps << endl;
            
//            char* begin = bigArrayPointer;
            
//            cout << "add" << &begin << endl;
            
//            this -> copyInternBufferIntoBigStorage();
            
//            cout << "add" << &begin << endl;

// WHITESPACE,NEWLINE,COMMENT1,COMMENT2

            state = automat -> getLastFinalState();
            
            if(state != WHITESPACE && state != NEWLINE && state != COMMENT1 && state != COMMENT2){
            
                char begin[wordSize+2];
                char* beginPointer=begin;
            
                for(int i=0;i<wordSize;i++){
                    *beginPointer++=internBuffer[i];
                }
            
                *beginPointer++ = '\0';
            
                int row=automat -> getRow();
                int col=automat -> getCol();
                
                token = createNewToken(state,row,col);
            
                switch(state){
                case NUMBER:
                            char* t;
                            token -> setNumValue(strtol(begin,&t,10));
                            break;
                
/*                case EXCEPTION:
                            cout << "Exception in " << row << "/" << col << endl;
                            cout << "near "<< c << ":::";
                            
                            cout << endl << "back" <<  backSteps << endl;
                            
                            for(int i=0;i<wordSize;i++){
                                cout << internBuffer[i];
                            }
                            
                            
                            
                            cout << endl << endl;*/
//                            exit(-1);
                            
//                            break;
                
                default:
            
                    Container* container = createContainer(begin,state);
                    token -> setContainer(container);
                    break;
                }
            
            }
            
//            cout << "---------------- " << internBuffer << endl;
            
            automat -> reset();
            rejectChars(backSteps);
            this -> resetInternBuffer();
            
            
            
        }
    }
    
    return token;

}

// zuruecksetzen der Zeichen intern und im Buffer
void Scanner::rejectChars(int amount){
    buffer->resetBy(backSteps);
    wordSize -= amount;
//    bigArrayPointer -= amount;
}

// Tokenerstellung mit ermittelten Daten
Token* Scanner::createNewToken(State state,int row,int col){
    return new Token(state,row,col);
}

// TODO durchsuchen der Hashmap
Container* Scanner::createContainer(char* word,State state){
    
    Container* container = hashMap -> get(word);
    
//    cout << "n:" << endl<<word<<endl<<endl;
    
    if(!container){
        
        
        char* begin=bigArrayPointer;
        this -> copyInternBufferIntoBigStorage();
        
        if(MAX_STORAGE - ((int)(containerBlockPointer - startContainerBlock)) == 0){
            this -> createContainerSpace();
        }
        
        *containerBlockPointer = Container(begin,state);
        container = containerBlockPointer;
        containerBlockPointer++;
        
        hashMap -> add(container);
        
    }
    
    return container;
    
}

// Konstruktor initialisiert den Scanner
Scanner::Scanner(){
    this -> init();
}

// Aufräumen des Array
Scanner::~Scanner(){
    delete[] internBuffer;
    bigArrayPointer=0;
    containerBlockPointer=0;
    startBigArray=0;
    startContainerBlock=0;
}


// auf Ausgangswerte zuruecksetzen
void Scanner::resetInternBuffer(){
    this -> wordSize=0;
}

// Daten initialisieren
void Scanner::init(){
    this -> resetInternBuffer();
    this -> hashMap = new HashMap();
    this -> wordSize=0;
    
//    this -> internBuffer = this -> internBufferField;
    
    this -> containerList = LinkedList<Container*>();
    this -> wordList = LinkedList< GenericStorage<char> >();
    this -> createWordSpace();
    this -> createContainerSpace();
    
    this -> generateIdentifier("IF\0");
    this -> generateIdentifier("if\0");
    this -> generateIdentifier("WHILE\0");
    this -> generateIdentifier("while\0");
    this -> generateIdentifier("\0");
    
    cout << "END INIT" << endl;
}



// Erweiterung des Wortspeichers durch Anhaengen eines neuen Arrays
void Scanner::createContainerSpace(){
   
    Container bigArray[MAX_STORAGE];

    containerList.add(bigArray);
    containerBlockPointer = containerList.get(containerList.getSize()-1) -> getValue();
    startContainerBlock = containerBlockPointer;
}

// Erweiterung des Wortspeichers durch Anhaengen eines neuen Arrays
void Scanner::createWordSpace(){
   
    wordList.add(GenericStorage<char>());
    bigArrayPointer = wordList.get(wordList.getSize()-1) -> getValue() . getField();
    startBigArray = bigArrayPointer;
}

// Erstellung von Schluesselwoertern samt dazugehoerigen Kontainer
// Speicherung in den angebotenen Speicherfeldern
void Scanner::generateIdentifier(char* ident){

    this -> resetInternBuffer();
    
    //cout << "ident"<<ident<<endl;
    
    char* begin=internBuffer;
    
    while(*ident){
    	//cout << "--"<<*ident;
        this -> addIntoInternBuffer(*ident++);
    }
    
//    cout << "internB "<< internBuffer << endl;
    
//    cout << "bigArrayPointer"<<bigArrayPointer<<endl;

    
            
//            cout << "ad" << &begin << endl;
            
    State state = IDENTIFIER;
    createContainer(begin,state);

}

// kopiert den internen Buffer in den festen Speicher
void Scanner::copyInternBufferIntoBigStorage(){

//    cout << "free" << (MAX_STORAGE - ((int)(bigArrayPointer - startBigArray)) )<< endl;
    
    int used=(int)(bigArrayPointer - startBigArray);
    
//    cout << "used" << used << endl;
    
    if(wordSize > used){
        this -> createWordSpace();
    }
    

    for(int i=0;i<wordSize;i++){
        *bigArrayPointer++=internBuffer[i];
//        cout << "|"<<internBuffer[i]<<endl;
    }
            
    // anhaengen des Nullbits, um Wortende zu signalisieren
    *bigArrayPointer++ = '\0';
    
}

// das Zeichen in den internen Speichern einfuegen
void Scanner::addIntoInternBuffer(char c){
    
    const int size = sizeof(*internBuffer);
    //cout << size << endl;
    
/*    if(wordSize >= size){
        
        char temp[2*size];
        memcpy(temp,internBuffer,wordSize);
        cout << temp << endl;
        
        // Speicherleak?
//        delete internBuffer;
        this -> internBuffer = temp;
        
    }*/
    
  /*  if(wordSize >= size){
    
        char temp[2*size];
        internBuffer=&(temp[0]);
        memcpy(internBuffer,temp,2*size);
        delete internBuffer;
        internBuffer=temp;
    
    }*/
    
//    cout << "internBuffer"<<internBuffer << endl;
    internBuffer[wordSize++] = c;
    
}

/**void Scanner::addIntoInternBuffer(char* c){
    
    
    if(wordSize >= wordLimit){
    
        wordLimit*=2;
        char temp[wordLimit];
        internBuffer=temp;
        
//        memcpy(temp,temp,size);
//        delete internBuffer;
//        internBuffer=temp;
    
    }

    internBuffer[wordSize++]=*c;
    col++;
    
    cout << "#" << *c << internBuffer[wordSize-2] << endl;
}
**/


// main-Methode zum Testen
int main(int argc, char* argv[]){

	if (argc < 1) {
		cout << "fail" <<endl;
		return EXIT_FAILURE;
	}

	Automat *automat = new Automat();
	Buffer *buffer = new Buffer(argv[1]);
	Scanner *scanner = new Scanner();


    Token* token;

    int i=70;
    Container* container;

    int ctr=0;
    char c;

    /*do{

        c=buffer -> nextChar();
        cout << c << endl;
        ctr++;

    }while(c);

    buffer -> resetBy(ctr);*/


    do{
    	cout << "ich bin im do while" << endl;
        token=scanner->nextToken();
        cout << "ich lieferte ein Token" << endl;
        container = token -> getContainer();
        cout << "TOKEN: "<< automat->enumToString(container?container->getType():NUMBER) << ":" << token -> getRow() << "/" << token -> getCol()<< endl;
//        cout <<"t"<< token->getType() <<":" << endl;

        if(token -> getType()==NUMBER){
            cout << "# " << token -> getNumValue();
        }else{
            cout << token -> getContainer() -> getValue();
        }
        cout << endl << endl;
        i--;
    }while(token->getType()!=EOF2 &&1);

    cout << "END" << endl;

}


