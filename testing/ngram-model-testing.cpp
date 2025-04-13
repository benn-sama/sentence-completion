
#include "../ngram_model.hpp"
#include "../text_utils.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

// Helper function to check if two doubles are approximately equal
bool approxEqual(double a, double b, double epsilon = 0.0001) {
    return std::abs(a - b) < epsilon;
}

void printTestResult(const std::string& testName, bool passed, double actual = 0.0, double expected = 0.0) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED");
    if (!passed) {
        std::cout << " (Expected: " << expected << ", Actual: " << actual << ")";
    }
    std::cout << std::endl;
}

// Test the construction and training of the model
void testTraining() {
    NGramModel model;
    std::string text = loadTextFile("testing/text-for-probability.txt");
    if (text.empty()) {
        throw std::invalid_argument("FILE ERROR: FILE NOT OPEN");
    }
    
    std::string clean = cleanText(text);
    std::vector<std::string> words = tokenize(clean);
    auto bigrams = generateBigrams(words);
    model.train(bigrams);
    
    // Test a few unigram counts
    bool test1 = model.getUnigramCount("the") > 0;
    bool test2 = model.getUnigramCount("cat") > 0;
    bool test3 = model.getUnigramCount("nonexistent") == -3;
    
    printTestResult("Training - Unigram Count Test 1", test1);
    printTestResult("Training - Unigram Count Test 2", test2);
    printTestResult("Training - Unigram Count Test 3", test3);
}

// Test probability calculations
void testProbabilities() {
    NGramModel model;

    std::string text = loadTextFile("testing/text-for-probability.txt");
    if (text.empty()) {
        throw std::invalid_argument("FILE ERROR: FILE NOT OPEN");
    }
    std::string cleaned = cleanText(text);
    std::vector<std::string> words = tokenize(cleaned);
    auto bigrams = generateBigrams(words);
    model.train(bigrams);
    
    // Test probability calculations
    // P(cat | the) = Count(the, cat) / Count(the)
    double probCatGivenThe = model.getProbability("the", "cat");
    // We need to verify this is correct based on our text
    // "the cat" appears 3 times, "the" appears 5 times total
    // So P(cat | the) should be 3/5 = 0.6
    bool test1 = approxEqual(probCatGivenThe, 0.6);
    
    // Test probability for a non-existent bigram
    double probNonExistent = model.getProbability("nonexistent", "word");
    bool test2 = approxEqual(probNonExistent, 0.0);
    
    // Test smoothed probability
    double smoothedProb = model.getSmoothedProbability("the", "cat");
    // With Laplace smoothing: P(cat | the) = (Count(the, cat) + 1) / (Count(the) + V)
    // Where V is vocabulary size
    // We can't directly test this without knowing V, but it should be > 0
    bool test3 = smoothedProb > 0.0;
    
    printTestResult("Probability - P(cat|the) Test", test1, probCatGivenThe, 0.6);
    printTestResult("Probability - Non-existent Bigram Test", test2, probNonExistent, 0.0);
    printTestResult("Probability - Smoothed Probability Test", test3, smoothedProb, 0.0);
}

// Test prediction functionality
void testPrediction() {
    std::cout  << "\n------------------------------------------------------------\n";
    std::cout << "TESTING N GRAM MODEl\n\n";
    std::cout  << "\n------------------TESTING testPrediction()------------------\n";
    NGramModel model;
    
    std::string text = loadTextFile("testing/text-for-probability.txt");
    if (text.empty()) {
        throw std::invalid_argument("FILE ERROR: FILE NOT OPEN");
    }
    std::string cleaned = cleanText(text);
    std::vector<std::string> words = tokenize(cleaned);
    auto bigrams = generateBigrams(words);
    model.train(bigrams);
    
    // Test predictNext
    std::string nextAfterThe = model.predictNext("the");
    std::cout << "HERE: " << nextAfterThe;
    // "the cat" appears more than any other bigram starting with "the"
    bool test1 = nextAfterThe == "cat";
    
    // Test topNextWords
    auto topWords = model.topNextWords("the", 3);
    bool test2 = topWords.size() > 0 && topWords.size() <= 3;
    
    // Test prediction for non-existent word
    std::string nextAfterNonExistent = model.predictNext("nonexistent");
    bool test3 = nextAfterNonExistent == "?";
    
    printTestResult("Prediction - Next After 'the' Test", test1);
    if (!test1) {
        std::cout << "  Predicted: \"" << nextAfterThe << "\", Expected: \"cat\"" << std::endl;
    }
    
    printTestResult("Prediction - Top Words Test", test2);
    if (!test2) {
        std::cout << "  Got " << topWords.size() << " words, expected between 1 and 3" << std::endl;
        std::cout << "  Words: ";
        for (const auto& word : topWords) {
            std::cout << "\"" << word << "\" ";
        }
        std::cout << std::endl;
    }
    
    printTestResult("Prediction - Non-existent Word Test", test3);
    if (!test3) {
        std::cout << "  Predicted: \"" << nextAfterNonExistent << "\", Expected: \"?\"" << std::endl;
    }
    
    std::cout  << "\n------------------FINISHED testPrediction()------------------\n";
}

// Test specific probability values
void testSpecificProbabilities() {
    std::cout  << "\n------------------TESTING testSpecificProabilities()------------------\n";
    NGramModel model;

    std::string text = loadTextFile("testing/text-for-probability.txt");
    if (text.empty()) {
        throw std::invalid_argument("FILE ERROR: FILE NOT OPEN");
    }
    std::string cleaned = cleanText(text);
    std::vector<std::string> words = tokenize(cleaned);
    auto bigrams = generateBigrams(words);
    model.train(bigrams);
    
    // In our text:
    // "the cat" appears 3 times
    // "cat paused", "cat stepped", "cat found", "cat through" each appear once
    
    // P(paused | cat) = Count(cat, paused) / Count(cat) = 1/4 = 0.25
    double probPausedGivenCat = model.getProbability("cat", "paused");
    bool test1 = approxEqual(probPausedGivenCat, 0.25);
    
    // P(door | silent) = Count(silent, door) / Count(silent) = 1/1 = 1.0
    double probDoorGivenSilent = model.getProbability("silent", "door");
    bool test2 = approxEqual(probDoorGivenSilent, 1.0);
    
    // P(nonexistent | cat) = 0
    double probNonExistentGivenCat = model.getProbability("cat", "nonexistent");
    bool test3 = approxEqual(probNonExistentGivenCat, 0.0);
    
    printTestResult("Specific Prob - P(paused|cat) = 0.25 Test", test1, probPausedGivenCat, 0.25);
    printTestResult("Specific Prob - P(door|silent) = 1.0 Test", test2, probDoorGivenSilent, 1.0);
    printTestResult("Specific Prob - P(nonexistent|cat) = 0 Test", test3, probNonExistentGivenCat, 0.0);
    std::cout  << "\n------------------FINISHED testSpecificProabilities()------------------\n";
    std::cout << "END OF TESTING N GRAM MODEL";
    std::cout  << "\n------------------------------------------------------------\n";
}

