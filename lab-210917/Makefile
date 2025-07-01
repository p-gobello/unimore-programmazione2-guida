CXX = g++
CXXFLAGS = -Wall -g

all: agenda

agenda: compito.o lista.o tipo.o
	$(CXX) $(CXXFLAGS) -o agenda compito.o lista.o tipo.o

compito.o: compito.cc lista.h tipo.h
	$(CXX) $(CXXFLAGS) -c compito.cc

lista.o: lista.cc lista.h tipo.h
	$(CXX) $(CXXFLAGS) -c lista.cc

tipo.o: tipo.cc tipo.h
	$(CXX) $(CXXFLAGS) -c tipo.cc

clean:
	rm -f *.o agenda
