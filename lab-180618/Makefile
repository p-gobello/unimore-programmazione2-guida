CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = test_bst
SOURCES = compito.cc bst.cc tipo.cc
OBJECTS = $(SOURCES:.cc=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
