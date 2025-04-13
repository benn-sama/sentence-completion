#include "../text_utils.hpp"  // Include the header, not the .cpp file

#include <iostream>
#include <fstream>
#include <stdexcept>

void testing_arbitrary_strings() {
  std::cout << "-----------------------TESTING ARBITRARY TXT FILE-------------------------\n";
  
  std::string filepath = "testing/testingText.txt"; // Adjust path as needed
  std::ifstream file(filepath);
  std::string line;

  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open file: " + filepath);
  }

  std::cout << "TESTING RAW TEXT: " << std::endl;
  std::cout << "------------------------------------------------\n";
  while (std::getline(file, line)) {
    std::cout << line << std::endl;
  }
  std::cout << "------------------------------------------------\n";

  file.close();

  std::string wholeText = loadTextFile(filepath);
  if (wholeText.empty()) {
    throw std::invalid_argument("Whole text is empty");
  }

  std::string clean = cleanText(wholeText);

  std::cout << "TESTING WHOLE TEXT\n\n" << clean << std::endl;
  std::cout << "------------------------------------------------\n";
  std::cout << "TESTING TOKENS\n\n";

  std::vector<std::string> tokens = tokenize(clean);
  std::vector<std::pair<std::string, std::string>> bigrams = generateBigrams(tokens);

  for (size_t i = 0; i < tokens.size(); ++i) {
    std::cout << tokens[i] << " ";
    if ((i + 1) % 10 == 0) { 
      std::cout << std::endl;
    }
  }
  std::cout << "------------------------------------------------\n";
  std::cout << "TESTING BIGRAMS\n\n";
  for (size_t i = 0; i < bigrams.size(); ++i) {
    std::cout << bigrams[i].first << " " << bigrams[i].second << std::endl;
  }
  
  std::cout << "-----------------------FINISHED ARBITRARY TXT FILE-------------------------\n";
}