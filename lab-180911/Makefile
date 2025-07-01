CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = programa
SOURCES = main.cc liste.cc tipo.cc
OBJECTS = $(SOURCES:.cc=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
