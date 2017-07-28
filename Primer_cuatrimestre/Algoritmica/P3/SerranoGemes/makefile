CC= g++
FLAGS= -c -g -ansi -Wall -Wextra -std=c++11
EXE= pPrincipal

pPrincipal: pPrincipal.o Conjunto.o ClaseTiempo.o 
	$(CC) Conjunto.o pPrincipal.o ClaseTiempo.o -o pPrincipal
pPrincipal.o: pPrincipal.cpp Conjunto.hpp
	$(CC) pPrincipal.cpp $(FLAGS) -o pPrincipal.o	
Conjunto.o: Conjunto.cpp Conjunto.hpp
	$(CC) Conjunto.cpp $(FLAGS) -o Conjunto.o
ClaseTiempo.o: ClaseTiempo.cpp ClaseTiempo.hpp
	$(CC) ClaseTiempo.cpp $(FLAGS) -o ClaseTiempo.o
#maximoMinimo.o: maximoMinimo.cpp maximoMinimo.hpp Conjunto.hpp
#	$(CC) maximoMinimo.cpp $(FLAGS) maximoMinimo.o

clean:
	rm -f *.o $(EXE)