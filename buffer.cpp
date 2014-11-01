#include <iostream>
#include "buffer.h"

using namespace std;

Buffer::Buffer(){
	this->init();
}

Buffer::~Buffer(){
	delete[] text;
	text = 0;
}

char Buffer::nextChar(){

    return *(text++);

}

void Buffer::resetBy(int step){

    text-=step;

}

void Buffer::init(){

    text="12+3well!\0";

}

int main(){
	Buffer buffer;
	buffer.init();
	int i = 0;
	char a;
	while (i < 9){
		a = buffer.nextChar();
		cout << a << endl;
		i++;
	}
	buffer.resetBy(9);
	cout << buffer.nextChar();
}
