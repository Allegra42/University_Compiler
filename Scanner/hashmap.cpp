#ifndef __hashmap__
#define __hashmap__

#include "Automat.h"
#include "hashmap.h"
#include "container.h"
#include "linkedlist.cpp"

#include <iostream>
using namespace std;


bool equalStrings(char* c1,char* c2){

    //cout << "c1:" << c1 << endl;
    //cout << "c2:" << c2 << endl;

    while(*c1!='\0' && *c2!='\0'){
    
        if(*c1 != *c2)
            return false;
        
//        cout << *c1 << "|" << *c2 << endl;
        
        c1++;
        c2++;
        
//        cout << *c1 << "|" << *c2 << endl;
        
    }
    
    return *c1 == *c2;
    
}

void HashMap::init(){

}

// Ermittlung des Containers durch einen Zeichenkettenschluessel
Container* HashMap::get(char* key){

    uInt index = this -> calculateIndex(key);
    
    if(!field[index])
        return 0;
    
    LinkedList<Container*>* list = field[index];
    int size = list -> getSize();
    
    Container* container;
    char* value;
    bool match=false;
    
    for(int i=0;i<size && !match;i++){

        container = list -> get(i) -> getValue();
        value = container -> getValue();
        
        match = equalStrings(key,value);
        
    }
    
    cout << "MATCHED IN MAP: " << match << endl;
    
    if(!match)
        container=0;
    
    return container;
    
    
//    uInt index=this->calculateIndex(key);
//    return field[index];
    
}

// Ermittlung des Indexes 
uInt HashMap::calculateIndex(char* numbers){

    char c;
    uInt index=0;
    
    do{
    
        c=*numbers;
        numbers++;
        index=(index*100+(uInt)c) % 2048;
    
    }while(c); 
    
    return index;   
    
}

// Hinzufuegen in die Hashmap
void HashMap::add(Container* container){

    char* key = container -> getValue();
    uInt index = this -> calculateIndex(key);
    
//    cout << "key:"<<key << endl;
    
    if(!field[index]){
    
        field[index]=new LinkedList<Container*>();
    
    }
    
    field[index] -> add(container);

//    int index=this -> calculateIndex(container -> getValue() );
//    field[index]=container;
    
//    return field[index];
}
/*
int main(){

    HashMap* map=new HashMap();
    
    cout << map -> get("abc\0") << endl;
    
    Container* container = new Container("abd\0",NUMBER);
    map -> add(container);
    
    cout << map -> get("abc\0") << endl;
    

}*/

#endif
