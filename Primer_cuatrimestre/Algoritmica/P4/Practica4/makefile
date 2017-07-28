CC= g++
EXE= pPrincipal
FLAGS= -c -g -ansi -Wall -Wextra -std=c++11


all: $(EXE)

pPrincipal: pPrincipal.o mochila.o material.o
	$(CC) $^ -o $@
pPrincipal.o: pPrincipal.cpp mochila.hpp material.hpp
	$(CC) pPrincipal.cpp $(FLAGS) -o $@
material.o: material.cpp material.hpp
	$(CC) material.cpp $(FLAGS) -o $@
mochila.o: mochila.cpp mochila.hpp material.hpp
	$(CC) mochila.cpp $(FLAGS) -o $@

clean:
	rm -f *.o $(EXE)