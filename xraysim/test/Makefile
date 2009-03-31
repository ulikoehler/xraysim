CXXFLAGS=-I../include -O0
CXXDEBUGFLAGS=-g -DDEBUG
OBJECTS=../build/matrixtask.o ../build/matrix.o

matrix.o:
		g++ -c -o ../build/matrix.o ../src/matrix.cpp

matrixtask.o:
		g++ -c -o ../build/matrixtask.o ../src/matrixtask.cpp

objects: matrix.o matrixtask.o

all: objects
	g++ $(CXXFLAGS) testmain.cpp $(OBJECTS) -o xraysim-test

debug:
		g++ $(CXXFLAGS) $(CXXDEBUGFLAGS) testmain.cpp $(OBJECTS) -o xraysim-test