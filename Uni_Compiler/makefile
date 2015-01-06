
## when just wanted to have a single scanner ##
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

syntax_c.o: Syntax_Check.h Syntax_Check.cpp
	g++ -c -g -o syntax_c.o Syntax_Check.cpp

scanner:	       buffer.o automat.o scanner.o token.o hashmap.o container.o node.h linkedlist.h genericStorage.h states.o
	g++ -o scanner buffer.o automat.o scanner.o token.o hashmap.o container.o node.h linkedlist.h genericStorage.h states.o

parser: syntax_c.o buffer.o automat.o scanner.o token.o hashmap.o container.o node.h linkedlist.h genericStorage.h states.o
	g++ -o parser token.o syntax_c.o buffer.o automat.o scanner.o hashmap.o container.o node.h linkedlist.h genericStorage.h states.o

## shared lib stuff ##

s_token.o: token.h token.cpp
	gcc -fPIC -Wall -g -c -o s_token.o token.cpp

s_hashmap.o: hashmap.h hashmap.cpp 
	gcc -fPIC -Wall -g -c -o s_hashmap.o hashmap.cpp 

s_buffer.o: buffer.cpp buffer.h
	gcc -fPIC -Wall -g -c -o s_buffer.o buffer.cpp

s_states.o: States.cpp States.h
	gcc -fPIC -Wall -g -c -o s_states.o States.cpp

s_automat.o: Automat.cpp Automat.h
	gcc -fPIC -Wall -g -c -o s_automat.o Automat.cpp

s_container.o: container.cpp container.h
	gcc -fPIC -Wall -g -c -o s_container.o container.cpp

s_scanner.o: scanner.cpp scanner.h 
	gcc -fPIC -Wall -g -c -o s_scanner.o scanner.cpp 

s_scanner:	       s_buffer.o s_automat.o s_scanner.o s_token.o s_hashmap.o s_container.o node.h linkedlist.h genericStorage.h s_states.o
	gcc -ggdb3 -shared -Wl,-soname,scanner.so.1 -o scanner.so.1.0 s_buffer.o s_automat.o s_scanner.o s_token.o s_hashmap.o s_container.o s_states.o -lc
	
	
	
	
	
