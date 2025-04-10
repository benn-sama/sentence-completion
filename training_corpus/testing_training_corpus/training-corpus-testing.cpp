#include "../database.hpp"

#include <iostream>

void testing_empty_database() {
  std::cout  << "\n------------------TESTING testing_empty_database()------------------\n";
  Database db(10);

  if (db.returnFirstWordCount("") != -1) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -1 after a empty parameter.";
    throw std::invalid_argument("ERROR");
  }

  if (db.returnFirstWordCount("machine learning") != -2) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -2 when string contains 2 words.\n";
    throw std::invalid_argument("ERROR");
  }

  if (db.returnFirstWordCount("machine") != -3) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -3 when string is not found.\n";
    throw std::invalid_argument("ERROR");
  }

  db.insert("machine");
  if (db.returnFirstWordCount("learning") != -3) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -3 when string is not found.\n";
    throw std::invalid_argument("ERROR");
  }

  db.insert("learning");
  if (db.returnFirstWordCount("the") != -3) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -3 when string is not found.\n";
    throw std::invalid_argument("ERROR");
  }

  if (db.returnSecondWordCount("", "learning") != -1) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -2 when 1st string is empty, but 2nd is not.\n";
    throw std::invalid_argument("ERROR");
  }

  if (db.returnSecondWordCount("", "") != -1) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -2 when both word strings are empty.\n";
    throw std::invalid_argument("ERROR");
  }

  if (db.returnSecondWordCount("machine", "") != -1) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -1 when 2nd string is empty.\n";
    throw std::invalid_argument("ERROR");
  }
  
  if (db.returnSecondWordCount("machine", "learning") != -2) {
    std::cerr << "\nFAIL: returnFirstWordCount()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return -3 when 2nd string is not found.\n";
    throw std::invalid_argument("ERROR");
  } 

  std::cout  << "\n------------------FINISHED testing_empty_database()------------------\n";
}

void addMultipleOfTheSameWord(Database& db, std::string word, int count) {
  for (int i = 0; i < count; ++i) {
    db.insert(word);
  }
}

void testing_single_words_only() {
  std::cout  << "\n------------------TESTING testing_single_words_only()------------------\n";
  Database db(10);

  db.insert("the");
  if (db.returnFirstWordCount("the") < 1) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nDoes not return 1 when the same word is inserted 1x.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Total Num of \"the\": " << db.returnFirstWordCount("the") << std::endl;

  addMultipleOfTheSameWord(db, "machine", 10);
  if (db.returnFirstWordCount("machine") < 10) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nDoes not return 10 when the same word is inserted 10x.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Total Num of \"machine\": " << db.returnFirstWordCount("machine") << std::endl;


  addMultipleOfTheSameWord(db, "learning", 15);
  if (db.returnFirstWordCount("learning") < 15) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nDoes not return 15 when the same word is inserted 15x.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Total Num of \"learning\": " << db.returnFirstWordCount("learning") << std::endl;

  db.insert("everyone is");
  if (db.returnFirstWordCount("everyone") < 1) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nFirst string wasn't inputted incorrectly. Value is not 1\n";
    std::cerr << "Total num of \"everyone\": " << db.returnFirstWordCount("everyone") << std::endl;
    throw std::invalid_argument("ERROR");
  }

  if (db.returnSecondWordCount("everyone", "is") < 1) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nSecond string wasn't inputted incorrectly. Value is not 1\n";
    std::cerr << "Total num of \"is\": " << db.returnSecondWordCount("everyone", "is") << std::endl;
    throw std::invalid_argument("ERROR");
  }

  std::cout  << "\n------------------FINISHED testing_single_words_only()------------------\n";
}

void testing_two_words_only() {
    std::cout  << "\n------------------TESTING testing_two_words_only()------------------\n";
  Database db(15);

  db.insert("machine learning");
  if (db.returnMostFrequentSecondWord("machine") != "learning") {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nDoes not return second word in string or inserted incorrectly.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "First word: machine" << "\nSecond word: " << db.returnMostFrequentSecondWord("machine") << std::endl;

  db.insert("machine people");
  db.insert("machine people");
  db.insert("machine people");
  db.insert("machine people");
  if (db.returnMostFrequentSecondWord("machine") != "people") {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nDoes not return most frequent second word in the second hashtable.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "\nMost frequent word after machine: " << db.returnMostFrequentSecondWord("machine") << std::endl;

  std::string secondWord = db.returnMostFrequentSecondWord("machine");
  if (db.returnSecondWordCount("machine", secondWord) < 4) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nMost frequent word count is incorrect.\n";
    std::cerr << secondWord << ": " << db.returnSecondWordCount("machine", secondWord) << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << secondWord << ": " << db.returnSecondWordCount("machine", secondWord) << std::endl;

  std::cout  << "\n------------------FINISHED testing_two_words_only()------------------\n";
}

void testing_both_words_simultaneously() {
  std::cout << "\n------------------TESTING testing_both_words_simultaneously()------------------\n";
  Database db(20);

  db.insert("artificial");
  if (db.returnFirstWordCount("artificial") != 1) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nSingle word not inserted correctly into singleWord hashtable.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 1: Successfully added 'artificial' to singleWord hashtable." << std::endl;

  db.insert("artificial intelligence");
  if (db.returnFirstWordCount("artificial") != 2) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nFirst word count not incremented in singleWord hashtable.\n";
    throw std::invalid_argument("ERROR");
  }
  if (db.returnSecondWordCount("artificial", "intelligence") != 1) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nTwo-word phrase not inserted correctly in doubleWord hashtable.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 2: Successfully added 'artificial intelligence' to both hashtables." << std::endl;

  db.insert("artificial neural");
  if (db.returnFirstWordCount("artificial") != 3) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nFirst word count not incremented correctly.\n";
    throw std::invalid_argument("ERROR");
  }
  if (db.returnSecondWordCount("artificial", "neural") != 1) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nSecond word pair not inserted correctly.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 3: Successfully added 'artificial neural' to both hashtables." << std::endl;

  db.insert("artificial intelligence");
  db.insert("artificial intelligence");
  if (db.returnFirstWordCount("artificial") != 5) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nFirst word count incorrect after multiple inserts.\n";
    std::cerr << "Expected: 5, Got: " << db.returnFirstWordCount("artificial") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  if (db.returnSecondWordCount("artificial", "intelligence") != 3) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nSecond word count incorrect after multiple inserts.\n";
    std::cerr << "Expected: 3, Got: " << db.returnSecondWordCount("artificial", "intelligence") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 4: Successfully verified multiple inserts of the same two-word phrase." << std::endl;

  if (db.returnMostFrequentSecondWord("artificial") != "intelligence") {
    std::cerr << "\nFAIL: returnMostFrequentSecondWord()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return the most frequent second word.\n";
    std::cerr << "Expected: intelligence, Got: " << db.returnMostFrequentSecondWord("artificial") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 5: Successfully verified the most frequent word after 'artificial' is 'intelligence'." << std::endl;

  std::vector<std::pair<std::string, int>> wordPairs = db.returnMultipleSecondWords("artificial", 2);
  bool foundIntelligence = false;
  bool foundNeural = false;

  for (const auto& pair : wordPairs) {
    if (pair.first == "intelligence" && pair.second == 3) {
      foundIntelligence = true;
    } else if (pair.first == "neural" && pair.second == 1) {
      foundNeural = true;
    }
  }

  if (!foundIntelligence || !foundNeural) {
    std::cerr << "\nFAIL: returnMultipleSecondWords()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return all expected second words with correct counts.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 6: Successfully retrieved multiple second words for 'artificial'." << std::endl;

  db.insert("deep");
  db.insert("deep learning");

  if (db.returnFirstWordCount("deep") != 2) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nSingle word count incorrect after both single and two-word inserts.\n";
    throw std::invalid_argument("ERROR");
  }
  
  if (db.returnSecondWordCount("deep", "learning") != 1) {
    std::cerr << "\nFAIL: insert(string)\nLINE: " << std::to_string(__LINE__) << "\nTwo-word count incorrect.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 7: Successfully verified interaction between single and two-word insertions." << std::endl;

  std::cout << "\n------------------FINISHED testing_both_words_simultaneously()------------------\n";
}

void testing_returning_most_frequent_second_word() {
  std::cout << "\n------------------TESTING testing_returning_most_frequent_second_word()------------------\n";
  Database db(20);

  if (db.returnMostFrequentSecondWord("neural") != "") {
    std::cerr << "\nFAIL: returnMostFrequentSecondWord()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return empty string when first word doesn't exist in database.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 1: Successfully verified empty response for non-existent first word." << std::endl;

  db.insert("neural networks");
  if (db.returnMostFrequentSecondWord("neural") != "networks") {
    std::cerr << "\nFAIL: returnMostFrequentSecondWord()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return correct second word after single insert.\n";
    std::cerr << "Expected: networks, Got: " << db.returnMostFrequentSecondWord("neural") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 2: Successfully retrieved 'networks' as most frequent word after 'neural'." << std::endl;

  db.insert("neural connections");
  db.insert("neural connections");
  if (db.returnMostFrequentSecondWord("neural") != "connections") {
    std::cerr << "\nFAIL: returnMostFrequentSecondWord()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return the most frequent second word after counts change.\n";
    std::cerr << "Expected: connections, Got: " << db.returnMostFrequentSecondWord("neural") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 3: Successfully updated most frequent word to 'connections'." << std::endl;

  db.insert("deep learning");
  if (db.returnMostFrequentSecondWord("deep") != "learning") {
    std::cerr << "\nFAIL: returnMostFrequentSecondWord()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return the correct second word for newly added pair.\n";
    std::cerr << "Expected: learning, Got: " << db.returnMostFrequentSecondWord("deep") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 4: Successfully retrieved 'learning' as most frequent word after 'deep'." << std::endl;

  db.insert("machine learning");
  db.insert("machine intelligence");
  db.insert("machine learning");
  db.insert("machine vision");
  db.insert("machine learning");
  if (db.returnMostFrequentSecondWord("machine") != "learning") {
    std::cerr << "\nFAIL: returnMostFrequentSecondWord()\nLINE: " << std::to_string(__LINE__) << "\nDoes not return the correct most frequent second word.\n";
    std::cerr << "Expected: learning, Got: " << db.returnMostFrequentSecondWord("machine") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 5: Successfully retrieved 'learning' as most frequent word after 'machine'." << std::endl;

  db.insert("machine vision");
  db.insert("machine vision");
  db.insert("machine vision");
  db.insert("machine vision");
  if (db.returnMostFrequentSecondWord("machine") != "vision") {
    std::cerr << "\nFAIL: returnMostFrequentSecondWord()\nLINE: " << std::to_string(__LINE__) << "\nDoes not update most frequent word after counts change.\n";
    std::cerr << "Expected: vision, Got: " << db.returnMostFrequentSecondWord("machine") << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 6: Successfully updated most frequent word to 'vision'." << std::endl;

  std::cout << "\n------------------FINISHED testing_returning_most_frequent_second_word()------------------\n";
}

void testing_return_multiple_second_words() {
  std::cout << "\n------------------TESTING testing_return_multiple_second_words()------------------\n";
  Database db(20);

  std::vector<std::pair<std::string, int>> emptyResult = db.returnMultipleSecondWords("machine", 3);
  if (!emptyResult.empty()) {
    std::cerr << "\nFAIL: returnMultipleSecondWords()\nLINE: " << std::to_string(__LINE__) << "\nShould return empty vector for non-existent word.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 1: Successfully verified empty response for non-existent word." << std::endl;

  db.insert("machine learning");
  db.insert("machine vision");
  db.insert("machine learning");
  db.insert("machine intelligence");
  db.insert("machine vision");
  db.insert("machine learning");

  std::vector<std::pair<std::string, int>> results = db.returnMultipleSecondWords("machine", 2);
  
  // Should return top 2 most frequent words
  if (results.size() != 2) {
    std::cerr << "\nFAIL: returnMultipleSecondWords()\nLINE: " << std::to_string(__LINE__) << "\nDid not return exactly 2 results.\n";
    std::cerr << "Expected: 2, Got: " << results.size() << std::endl;
    throw std::invalid_argument("ERROR");
  }

  bool foundLearning = false;
  bool foundVision = false;

  for (const auto& pair : results) {
    if (pair.first == "learning" && pair.second == 3) {
      foundLearning = true;
    } else if (pair.first == "vision" && pair.second == 2) {
      foundVision = true;
    }
  }

  if (!foundLearning || !foundVision) {
    std::cerr << "\nFAIL: returnMultipleSecondWords()\nLINE: " << std::to_string(__LINE__) << "\nDid not return correct top 2 words with frequencies.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 2: Successfully retrieved top 2 words for 'machine'." << std::endl;

  if (results[0].second < results[1].second) {
    std::cerr << "\nFAIL: returnMultipleSecondWords()\nLINE: " << std::to_string(__LINE__) << "\nResults are not ordered by frequency (highest first).\n";
    std::cerr << "First: " << results[0].first << " (" << results[0].second << "), Second: " << results[1].first << " (" << results[1].second << ")" << std::endl;
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 3: Successfully verified results are ordered by frequency." << std::endl;

  db.insert("machine code");
  std::vector<std::pair<std::string, int>> allResults = db.returnMultipleSecondWords("machine", 10);

  db.insert("deep learning");
  db.insert("deep learning");
  
  std::vector<std::pair<std::string, int>> deepResults = db.returnMultipleSecondWords("deep", 1);
  if (deepResults.size() != 1 || deepResults[0].first != "learning" || deepResults[0].second != 2) {
    std::cerr << "\nFAIL: returnMultipleSecondWords()\nLINE: " << std::to_string(__LINE__) << "\nDid not correctly isolate results for different first words.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 5: Successfully verified isolation between different first words." << std::endl;

  db.insert("unique word");
  std::vector<std::pair<std::string, int>> uniqueResult = db.returnMultipleSecondWords("unique", 1);
  
  if (uniqueResult.size() != 1 || uniqueResult[0].first != "word" || uniqueResult[0].second != 1) {
    std::cerr << "\nFAIL: returnMultipleSecondWords()\nLINE: " << std::to_string(__LINE__) << "\nDid not handle case with exactly one pair correctly.\n";
    throw std::invalid_argument("ERROR");
  }
  std::cout << "Test 6: Successfully handled case with exactly one pair." << std::endl;

  std::cout << "\n------------------FINISHED testing_return_multiple_second_words()------------------\n";
}

int main() {
  testing_empty_database();
  testing_single_words_only();
  testing_two_words_only();
  testing_both_words_simultaneously();
  testing_returning_most_frequent_second_word();
  testing_return_multiple_second_words();
}
