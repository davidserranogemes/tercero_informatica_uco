CC= g++
FLAGS= -c -g -ansi -Wall -std=c++11 
EXE= clienteUDP servidorUDP

all: $(EXE)

clienteUDP: clienteUDP.o
	$(CC) clienteUDP.o -o clienteUDP
clienteUDP.o: clienteUDP.c
	$(CC) clienteUDP.c $(FLAGS) -o clienteUDP.o

servidorUDP: servidorUDP.o 
	$(CC) servidorUDP.o -o servidorUDP
servidorUDP.o: servidorUDP.c
	$(CC) servidorUDP.c $(FLAGS) -o servidorUDP.o


clean:
	rm -f *.o $(EXE)