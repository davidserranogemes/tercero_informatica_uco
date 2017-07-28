
EXE= vseg

all: $(EXE)

vseg: vseg.cc
	g++ -Wall -o $(EXE) vseg.cc `pkg-config opencv --cflags --libs` -std=c++11 -g


clean:
	rm -f vseg