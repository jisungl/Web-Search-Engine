CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

all: ex10

ex10: ex10.o Vector.o
	$(CXX) $(CXXFLAGS) -o ex10 ex10.o Vector.o

ex10.o: ex10.cc Vector.h
	$(CXX) $(CXXFLAGS) -c ex10.cc

Vector.o: Vector.cc Vector.h
	$(CXX) $(CXXFLAGS) -c Vector.cc

clean:
	rm -f ex10 *.o *~