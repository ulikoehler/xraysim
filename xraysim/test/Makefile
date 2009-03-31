CXXFLAGS=-I../include -O0
CXXDEBUGFLAGS=-g -DDEBUG
OBJECTS=../build/matrixtask.o ../build/matrix.o ../build/testmain.o

all: objects
	g++ $(CXXFLAGS) $(OBJECTS) -o xraysim-test
		
objects:
		g++ -c -o ../build/matrix.o ../src/matrix.cpp
		g++ -c -o ../build/matrixtask.o ../src/matrixtask.cpp
		g++ -c -o ../build/testmain.o testmain.cpp

debug:
		g++ $(CXXFLAGS) $(CXXDEBUGFLAGS) testmain.cpp $(OBJECTS) -o xraysim-test

clean:
		rm -f xraysim-test ../build/*.o