CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: program

program: main.o matching.o Group.o
	$(CXX) $(CXXFLAGS) -o program main.o matching.o Group.o

main.o: main.cc matching.h Group.h
	$(CXX) $(CXXFLAGS) -c main.cc

matching.o: matching.cc matching.h Group.h
	$(CXX) $(CXXFLAGS) -c matching.cc

Group.o: Group.cc Group.h
	$(CXX) $(CXXFLAGS) -c Group.cc

clean:
	rm -f *.o program
