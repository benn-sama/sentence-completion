# Compiler
CXX = g++
CXXFLAGS = -std=c++14

# Target executable name
TARGET = main
TEST_TARGET = training-corpus-test
NGRAM_TEST_TARGET = test_for_ngram_model

# Source files
SRC = main.cpp text_utils.cpp training_corpus/database.cpp ngram_model.cpp real_time_typing.cpp
# Separately list all test source files
TEST_SRC = training_corpus/testing_training_corpus/training-corpus-testing.cpp training_corpus/database.cpp testing/utils-testing.cpp testing/test-all.cpp text_utils.cpp testing/ngram-model-testing.cpp  ngram_model.cpp
NGRAM_TEST_SRC = test_for_ngram_model.cpp ngram_model.cpp

# Object files
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Compile each test source file separately to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TEST_OBJ) -o $(TEST_TARGET)

$(NGRAM_TEST_TARGET): $(NGRAM_TEST_SRC)
	$(CXX) $(CXXFLAGS) $(NGRAM_TEST_SRC) -o $(NGRAM_TEST_TARGET)

# Run targets
run-main: $(TARGET)
	./$(TARGET)

run-test: $(TEST_TARGET)
	./$(TEST_TARGET)

run-ngram-test: $(NGRAM_TEST_TARGET)
	./$(NGRAM_TEST_TARGET)

# Clean rule
clean:
	@if [ -f $(TARGET) ]; then rm -f $(TARGET); fi || del /f /q $(TARGET)
	@if [ -f $(TEST_TARGET) ]; then rm -f $(TEST_TARGET); fi || del /f /q $(TEST_TARGET)
	@if [ -f $(NGRAM_TEST_TARGET) ]; then rm -f $(NGRAM_TEST_TARGET); fi || del /f /q $(NGRAM_TEST_TARGET)
	@rm -f $(TEST_OBJ) 2>/dev/null || true