CC= g++
EXE= pPrincipal
FLAGS= -c -g -ansi -Wall -Wextra -std=c++11

all: $(EXE)

pPrincipal: pPrincipal.o ochoReinas.o
	$(CC) $^ -o $@
pPrincipal.o: pPrincipal.cpp ochoReinas.hpp
	$(CC) pPrincipal.cpp $(FLAGS) -o $@
ochoReinas.o: ochoReinas.cpp ochoReinas.hpp
	$(CC) ochoReinas.cpp $(FLAGS) -o $@



clean:
	rm *.o $(EXE)