CXX = g++
CXXFLAGS = -Wall -g

all: agenda

agenda: main.o lista.o tipo.o
	$(CXX) $(CXXFLAGS) -o agenda main.o lista.o tipo.o

main.o: main.cc lista.h tipo.h
	$(CXX) $(CXXFLAGS) -c main.cc

lista.o: lista.cc lista.h tipo.h
	$(CXX) $(CXXFLAGS) -c lista.cc

tipo.o: tipo.cc tipo.h
	$(CXX) $(CXXFLAGS) -c tipo.cc

clean:
	rm -f *.o agenda
