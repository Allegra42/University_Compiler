/*
 * buffer.h
 *
 *  Created on: 30 Oct 2014
 *      Author: christian
 */

#ifndef BUFFERV2_H_
#define BUFFERV2_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>




class Buffer {
	public:
		Buffer(const char* filepath);
		~Buffer();
		char nextChar();
		void resetBy(int step);
		int main();

	private:
		void init();
		void readSector();
		void prevChar();
		void switchBuffer();

		char *buffer_pointer;
		char *buffer_pointer2;
		char *next;
		const char *filepath;
		const char* path;
		int buffer_number;
		int file_number;
		int read_bytes;
		unsigned long alignsize;
		unsigned long memsize;
		void *double_pointer;
		void *double_pointer2;

};

#endif /* BUFFERV2_H_ */
