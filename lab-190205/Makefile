CXX=g++
CXXFLAGS=-Wall -c 
LDFLAGS=
OBJS= compito.o tipo.o liste.o
EXEC=gioco

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXEC) $(OBJS)

compito.o: compito.cc tipo.h liste.h
	$(CXX) $(CXXFLAGS) compito.cc

tipo.o: tipo.cc tipo.h
	$(CXX) $(CXXFLAGS) tipo.cc

liste.o: liste.cc liste.h tipo.h
	$(CXX) $(CXXFLAGS) liste.cc

.PHONY: clean
clean:
	rm -f *.o $(EXEC)
