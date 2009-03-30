CXXFLAGS=-I../include -O0
CXXDEBUGFLAGS=-g -DDEBUG

all:
	g++ $(CXXFLAGS) testmain.cpp ../src/matrixtask.cpp -o xraysim-test

debug:
		g++ $(CXXFLAGS) $(CXXDEBUGFLAGS) testmain.cpp ../src/matrixtask.cpp -o xraysim-test