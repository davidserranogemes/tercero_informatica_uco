CC= g++
FLAGS= -c -g -ansi -Wall -std=c++11 
#-Wextra 
EXE= ruletaServidor ruletaCliente

all: $(EXE)

ruletaServidor: ruletaServidor.o ruleta_suerte.o serverFunction.o partida_ruleta.o
	$(CC) ruletaServidor.o ruleta_suerte.o serverFunction.o partida_ruleta.o -o ruletaServidor
ruletaCliente: ruletaCliente.o
	$(CC) ruletaCliente.o -o ruletaCliente
ruletaCliente.o: ruletaCliente.cpp constant.hpp
	$(CC) ruletaCliente.cpp $(FLAGS) -o ruletaCliente.o

serverFunction.o: serverFunction.cpp serverFunction.hpp constant.hpp ruleta_suerte.hpp
	$(CC) serverFunction.cpp $(FLAGS) -o serverFunction.o
partida_ruleta.o: partida_ruleta.cpp partida_ruleta.hpp constant.hpp
	$(CC) partida_ruleta.cpp $(FLAGS) -o partida_ruleta.o

ruleta_suerte.o: ruleta_suerte.cpp ruleta_suerte.hpp constant.hpp
	$(CC) ruleta_suerte.cpp $(FLAGS) -o ruleta_suerte.o

ruletaServidor.o: ruletaServidor.cpp constant.hpp serverFunction.hpp ruleta_suerte.hpp
	$(CC) ruletaServidor.cpp $(FLAGS) -o ruletaServidor.o
	
.PHONY: clean

clean:
	rm -f *.o test1 $(EXE)


