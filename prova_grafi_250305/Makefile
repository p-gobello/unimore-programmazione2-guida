# Makefile for prova_grafi_250305 project
# Bipartite graph system for product rating management

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g
TARGET = main
OBJS = compito.o grafo.o tipo.o

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Object files
compito.o: compito.cc grafo.h tipo.h
	$(CXX) $(CXXFLAGS) -c compito.cc

grafo.o: grafo.cc grafo.h
	$(CXX) $(CXXFLAGS) -c grafo.cc

tipo.o: tipo.cc tipo.h
	$(CXX) $(CXXFLAGS) -c tipo.cc

# Documentation with Doxygen
doc:
	doxygen

# Clean build files
clean:
	rm -f *.o $(TARGET)
	rm -rf doc/

# Clean everything including documentation
distclean: clean
	rm -rf doc/

# Install doxygen configuration if not present
doxyfile:
	doxygen -g

.PHONY: all clean distclean doc doxyfile
