CXXFLAGS=-I../include
CXXDEBUGFLAGS=-g -DDEBUG

all:
	g++ $(CXXFLAGS) testmain.cpp ../src/matrixtask.cpp -o xraysim-test

debug:
		g++ $(CXXFLAGS) $(CXXDEBUGFLAGS) testmain.cpp -o xraysim-test