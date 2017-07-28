EXE= lbpseg
CC=c++
all= $(EXE)

lbpseg: lbpseg.cpp funciones.cpp funciones.hpp Region.cpp Region.hpp
	$(CC) lbpseg.cpp funciones.cpp Region.cpp -o lbpseg `pkg-config opencv --cflags --libs` -std=c++11 -g
