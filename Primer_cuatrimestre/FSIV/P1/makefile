FLAGS= -c -g -Wall  -std=c++11
OPENCV= `pkg-config opencv --cflags --libs` 
CC= g++
EXE= getStats

all: $(EXE)

getStats: getStats.o
	$(CC) getStats.o $(OPENCV)-o getStats
getStats.o: getStats.cc
	$(CC) getStats.cc $(FLAGS) $(OPENCV) -o getStats.o


clean:
	rm -f *.o getStats