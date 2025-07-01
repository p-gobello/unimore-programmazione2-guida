CXX = g++
CXXFLAGS = -Wall -g

all: gioco

gioco: compito.o liste.o tipo.o
	$(CXX) $(CXXFLAGS) -o gioco compito.o liste.o tipo.o

compito.o: compito.cc liste.h tipo.h
	$(CXX) $(CXXFLAGS) -c compito.cc

liste.o: liste.cc liste.h tipo.h
	$(CXX) $(CXXFLAGS) -c liste.cc

tipo.o: tipo.cc tipo.h
	$(CXX) $(CXXFLAGS) -c tipo.cc

clean:
	rm -f *.o gioco
