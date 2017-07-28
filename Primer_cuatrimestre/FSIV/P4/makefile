EXE= getContours getDescriptor
CC=c++
FLAGS=`pkg-config opencv --cflags --libs` -std=c++11 -g

all: $(EXE)

getContours: getContours.cpp 
	$(CC) $^ -o getContours $(FLAGS)

getDescriptor: getDescriptor.cpp
	$(CC) $^ -o getDescriptor $(FLAGS)