CXX = g++
CXXFLAGS = -Wall -g -std=c++17

all: ex16

ex16: ex16.o SocketUtils.o
	$(CXX) $(CXXFLAGS) -o ex16 ex16.o SocketUtils.o

ex16.o: ex16.cc SocketUtils.h
	$(CXX) $(CXXFLAGS) -c ex16.cc

SocketUtils.o: SocketUtils.cc SocketUtils.h
	$(CXX) $(CXXFLAGS) -c SocketUtils.cc

clean:
	rm -f ex16 *.o *~