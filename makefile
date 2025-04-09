# Compiler
CXX = g++
CXXFLAGS = -std=c++11

# Target executable name
TARGET = main
TEST_TARGET = training-corpus-test

# Source files
SRC = main.cpp text_utils.cpp training_corpus/database.cpp ngram_model.cpp
TEST_SRC = training_corpus/testing_training_corpus/training-corpus-testing.cpp training_corpus/database.cpp

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_TARGET)

# Test rules
test: $(TEST_TARGET)
	./$(TEST_TARGET)

run-test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean rule
clean:
	@if [ -f $(TARGET) ]; then rm -f $(TARGET); fi || del /f /q $(TARGET)
	@if [ -f $(TEST_TARGET) ]; then rm -f $(TEST_TARGET); fi || del /f /q $(TEST_TARGET)