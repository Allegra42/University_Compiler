
token.o: token.h token.cpp
	g++ -c -g -o token.o token.cpp

hashmap.o: hashmap.h hashmap.cpp 
	g++ -c -g -o hashmap.o hashmap.cpp 

buffer.o: buffer.cpp buffer.h
	g++ -c -g -o buffer.o buffer.cpp

states.o: States.cpp States.h
	g++ -c -g -o states.o States.cpp

automat.o: Automat.cpp Automat.h
	g++ -c -g -o automat.o Automat.cpp

container.o: container.cpp container.h
	g++ -c -g -o container.o container.cpp

scanner.o: scanner.cpp scanner.h 
	g++ -c -g -o scanner.o scanner.cpp 

scanner:	       buffer.o automat.o scanner.o token.o hashmap.o container.o node.h linkedlist.h genericStorage.h states.o
	g++ -o scanner buffer.o automat.o scanner.o token.o hashmap.o container.o node.h linkedlist.h genericStorage.h states.o

