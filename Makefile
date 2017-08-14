CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -c #-Wall
CXXFLAGS += -g #debugging info
CXXFLAGS += -pedantic-errors

objects = base.o #nodeStruct.o

all: base

base: $(objects)
	$(CXX) $(objects) -o base

base.o: base.cpp nodeStruct.h nearestNeighbor.h
	$(CXX) $(CXXFLAGS) base.cpp

#nodeStruct.o: nodeStruct.h 
#	$(CXX) $(CXXFLAGS) nodeStruct.cpp

nearestNeighbor.o: nearestNeighbor.h nodeStruct.h
	$(CXX) $(CXXFLAGS) nearestNeighbor.cpp
clean: 
	rm -rf $(objects) base 
