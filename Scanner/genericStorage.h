

#ifndef __genericStorage_h__
#define __genericStorage_h__

const int MAX_STORAGE=10000;

template<class T> class GenericStorage{
    
    public:
        T* getField();
        
    private:
        T field[MAX_STORAGE];
    
};

template<class T> T* GenericStorage<T>::getField(){
    return field;
}

#endif
