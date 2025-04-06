#include "text_utils.hpp"
#include <fstream>
#include <sstream>
#include <cctype>     // for std::tolower, std::isalpha
#include <algorithm>  // for std::transform

std::string loadTextFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
      return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::string cleanText(const std::string& rawText) {
  std::string cleaned;
  for (char c : rawText) {
      if (std::isalpha(c) || std::isspace(c)) {
          cleaned += std::tolower(c);
      }
      // skip punctuation and symbols
  }
  return cleaned;
}

std::vector<std::string> tokenize(const std::string& text) {
  std::vector<std::string> words;
  std::istringstream stream(text);
  std::string word;
  while (stream >> word) {
      words.push_back(word);
  }
  return words;
}

std::vector<std::pair<std::string, std::string>> generateBigrams(const std::vector<std::string>& words) {
  std::vector<std::pair<std::string, std::string>> bigrams;
  for (size_t i = 0; i < words.size() - 1; ++i) {
      bigrams.emplace_back(words[i], words[i + 1]);
  }
  return bigrams;
}
