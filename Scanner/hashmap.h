#ifndef __hashmap_h__
#define __hashmap_h__

#include "container.h"
#include "linkedlist.h"

typedef unsigned int uInt;

class HashMap{

    public:
            void init();
            bool contains(char*);
            void add(Container*);
            Container* get(char*);
            
    private:
            LinkedList<Container*>* field[2048];
            uInt calculateIndex(char*);

};

#endif
