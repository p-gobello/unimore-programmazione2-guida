# Makefile for Hotel BST Management System

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g
TARGET = hotel_bst
OBJECTS = main.o bst.o tipo.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile main.cc
main.o: main.cc bst.h tipo.h
	$(CXX) $(CXXFLAGS) -c main.cc

# Compile bst.cc
bst.o: bst.cc bst.h tipo.h
	$(CXX) $(CXXFLAGS) -c bst.cc

# Compile tipo.cc
tipo.o: tipo.cc tipo.h
	$(CXX) $(CXXFLAGS) -c tipo.cc

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Test with valgrind for memory leaks
test-memory: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Print help
help:
	@echo "Available targets:"
	@echo "  all        - Build the executable (default)"
	@echo "  clean      - Remove object files and executable"
	@echo "  run        - Build and run the program"
	@echo "  test-memory- Run with valgrind for memory leak detection"
	@echo "  help       - Show this help message"

.PHONY: all clean run test-memory help
