#ifndef TEXT_UTILS_H
#define TEXT_UTILS_H

#include <string>
#include <vector>
#include <utility> // for std::pair

// Load full text file into a string
std::string loadTextFile(const std::string& filename);

// Clean text (remove punctuation, lowercase)
std::string cleanText(const std::string& rawText);

// Tokenize cleaned text into words
std::vector<std::string> tokenize(const std::string& text);

// Generate bigrams from word list
std::vector<std::pair<std::string, std::string>> generateBigrams(const std::vector<std::string>& words);

#endif
