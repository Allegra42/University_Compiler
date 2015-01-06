#ifndef __parser__
#define __parser__

#include "./parser.h"
using namespace std;

int main(){

    Parser* parser=new Parser("./testFiles/test");

}

Parser::Parser(char* filepath){

    scannerPointer = new Scanner(filepath);
    
}

Parser::~Parser(){

    delete scannerPointer;
    scannerPointer = 0;

}

#endif
