CC= g++
EXE= pPrincipal
FLAGS= -c -g -ansi -Wall -Wextra -std=c++11


all: $(EXE)

pPrincipal: pPrincipal.o mochila.o material.o cambio.o moneda.o fichero.o
	$(CC) $^ -o $@
pPrincipal.o: pPrincipal.cpp mochila.hpp material.hpp cambio.hpp moneda.hpp fichero.hpp
	$(CC) pPrincipal.cpp $(FLAGS) -o $@

material.o: material.cpp material.hpp
	$(CC) material.cpp $(FLAGS) -o $@
mochila.o: mochila.cpp mochila.hpp material.hpp
	$(CC) mochila.cpp $(FLAGS) -o $@

moneda.o: moneda.cpp moneda.hpp
	$(CC) moneda.cpp $(FLAGS) -o $@
cambio.o: cambio.cpp cambio.hpp moneda.hpp
	$(CC) cambio.cpp $(FLAGS) -o $@

fichero.o: fichero.cpp fichero.hpp mochila.hpp material.hpp cambio.hpp moneda.hpp
	$(CC) fichero.cpp $(FLAGS) -o $@

clean:
	rm -f *.o $(EXE)