CXXFLAGS=-I../include -O0
CXXDEBUGFLAGS=-g -DDEBUG
OBJECTS=../build/matrixtask.o ../build/matrix.o

objects:
	g++ -c -o ../build/matrixtask.o ../src/matrixtask.cpp
	g++ -c -o ../build/matrixtask.o ../src/matrix.cpp

all: objects
	g++ $(CXXFLAGS) testmain.cpp $(OBJECTS) -o xraysim-test

debug:
		g++ $(CXXFLAGS) $(CXXDEBUGFLAGS) testmain.cpp $(OBJECTS) -o xraysim-test