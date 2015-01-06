
#ifndef __node_h__
#define __node_h__

template<class T> class Node{

    public:
        
        Node(T t);
        
        ~Node();
        
        void setNext(Node<T>* n);
        
        Node<T>* getNext();
        
        T getValue();
        
    private:
        Node<T>* next;
        T value;
};

template<class T> Node<T>::Node(T t){
    value = t;
    next = 0;
}

template<class T> Node<T>::~Node(){
    next = 0;
}

template<class T> void Node<T>::setNext(Node* n){
    next = n;
}

template<class T> Node<T>* Node<T>::getNext(){
    return next;
}

template<class T> T Node<T>::getValue(){
    return value;
}

#endif
