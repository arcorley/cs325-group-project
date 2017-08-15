CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -c #-Wall
CXXFLAGS += -g #debugging info
CXXFLAGS += -pedantic-errors

objects = base.o nearestNeighbor.o

all: main

main : $(objects)
	$(CXX) $(objects) -o main

base.o: base.cpp nodeStruct.h nearestNeighbor.h
	$(CXX) $(CXXFLAGS) base.cpp

nearestNeighbor.o: nearestNeighbor.cpp nodeStruct.h
	$(CXX) $(CXXFLAGS) nearestNeighbor.cpp
clean: 
	rm -rf $(objects) main
