# Compiler
CXX = g++
CXXFLAGS = -std=c++11

# Target executable name
TARGET = main

# Source files
SRC = main.cpp

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)
