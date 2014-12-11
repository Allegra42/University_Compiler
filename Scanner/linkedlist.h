
#ifndef __linkedListHeader__
#define __linkedListHeader__


#include "node.h"
using namespace std;


template<class T> class LinkedList{

    public:
        
        LinkedList(){
            init();
        }
        
        ~LinkedList(){
            
            while(size){
                delete this -> get(size - 1);
                size--;
            }
            
            root = 0;
        }
        
        void add(T);
        Node<T>* get(int);
        
        int getSize(){
            return size;
        }
        
    private:
        Node<T>* root;
        int size;
        
        void init();

};



template<class T> Node<T>* LinkedList<T>::get(int index){

    if(index < 0 && index > size-1)
        return 0;
    
    Node<T>* n = root;
    
    while(index--){
    
        n = n -> getNext();
    
    }
    
    return n;
    
}

template<class T> void LinkedList<T>::add(T t){
    Node<T>* newNode = new Node<T>(t);

    if(!root){
    
        root = newNode;
    
    }else{
    
        Node<T>* n=root;
        
        while(n -> getNext()){
            n = n -> getNext();
        }
        
        n -> setNext(newNode);
    
    }
    
    size++;
    
}

template<class T> void LinkedList<T>::init(){
    root=0;
    size=0;
}


#endif
