
/*
 * buffer.cpp
 *
 *  Created on: 30 Oct 2014
 *      Author: christian
 */

#ifndef __BUFFERcpp__
#define __BUFFERcpp__

#include "buffer.h"

using namespace std;



/**
 * Konstruktor.
 */
Buffer::Buffer(const char *filepath){
	path = filepath;
	buffer_number = 0;
	alignsize = 512;
	memsize = 512;
	init();
	readSector();
}

/**
 * Destruktor.
 */
Buffer::~Buffer(){
	close(file_number);
	free(double_pointer);
	free(double_pointer2);
}

/**
 * Hilfsmethode zum Markieren des aktiven Speicherbereichs.
 */
void Buffer::switchBuffer(){
	if (buffer_number == 0){
				buffer_number = 1;
			} else {
				buffer_number = 0;
			}
}

/**
 * Ausgeben des nächsten Chars aus dem gelesenen Block.
 */
char Buffer::nextChar(){
	if(*next == '\0'){
		if(next == &buffer_pointer[memsize]){
			buffer_number = 1;
			this->readSector();
			next = buffer_pointer2;
			return *next++;
		} else if (next == &buffer_pointer2[memsize]){
			buffer_number = 0;
			this->readSector();
			next = buffer_pointer;
			return *next++;
		} else {
			*next++;
//			cout << "prelast" << endl;
			return '\0';
		}
	} else {
//	    cout << *next << "<-->" ;
		return *next++;
	}
}

/**
 * Hilfsmethode zum Zurücksetzen des Ausgabepointers.
 */
void Buffer::prevChar(){
	if(next == &buffer_pointer[0]){
			buffer_number = 1;
			*next = *(buffer_pointer2 + (memsize-1));
	} else if (next == &buffer_pointer2[0]){
		buffer_number = 0;
		*next = *(buffer_pointer + (memsize-1));
	}
	next--;
}

/**
 * Zurücksetzen des Ausgabepointers.
 * @param step Anzahl der Schritte, die den Pointer zurücksetzen.
 */
void Buffer::resetBy(int step){
    while (step > 0){
    	prevChar();
    	step--;
    }
}

/**
 * Initialisiert den Buffer:
 */
void Buffer::init(){
//	cout << "### init buffer..." << endl;

	int test = posix_memalign(&double_pointer, alignsize, memsize); 	//Speicherplatz Teil 1 anlegen.
	if(test != 0){
		cout << "### Buffer 1: Error!" << endl;
	}
	//memset(double_pointer, 0, memsize);

	int test2 = posix_memalign(&double_pointer2, alignsize, memsize); 	//Speicherplatz Teil 2 anlegen.
	if(test2 != 0){
		cout << "### Buffer 2: Error!" << endl;
	}
	//memset(double_pointer2, 0, memsize);

	buffer_pointer = (char*) double_pointer;							//Pointer am Anfang der Speicherbereiche auf
	buffer_pointer2 = (char*) double_pointer2;							//char* casten, um die Characters auszulesen.

	file_number = open(path, O_DIRECT);									//Text-File öffnen
	next = buffer_pointer;
}

/**
 * Liest aus dem File aus -> der übergebene Pointer wird
 * auf den Beginn des ausgelesenen Sektors gelegt.
 */
void Buffer::readSector(){
	switch(buffer_number){
		case 1: 	read_bytes = read(file_number, buffer_pointer2, memsize);
					if(read_bytes < 512){
						*(buffer_pointer2 + (read_bytes)) = 0;
					}
			break;
		default:	read_bytes = read(file_number, buffer_pointer, memsize);
					if(read_bytes < 512){
						*(buffer_pointer + (read_bytes)) = 0;
					}
			break;
	}
}


//int main(){
//	const char* file_location = "/home/christian/WorkspaceC++/Buffer_v2/Test2.txt";
//	Buffer buffer = Buffer(file_location);
//	int a = 0;
//	while(a <= 100){
//		char x = buffer.nextChar();
//		if(x != '\0'){
//			cout << x << flush;
//			a++;
//		} else {
//			break;
//		}
//	}
//	cout << flush << endl;
//	buffer.resetBy(15);
//	cout << "\n #####ResetBy" << endl;
//	int b = 0;
//	while(b < 15){
//		cout << buffer.nextChar();
//		b++;
//	}
//}

#endif

// '\0' - aktuelles Zeichen == 0

