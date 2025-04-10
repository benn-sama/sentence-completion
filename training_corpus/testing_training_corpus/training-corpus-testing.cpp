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

  

  std::cout  << "\n------------------FINISHED testing_two_words_only()------------------\n";
}

void testing_both_words_simultaneously() {

}

void testing_returning_most_frequent_second_word() {
  
}

int main() {
  testing_empty_database();
  testing_single_words_only();
  testing_two_words_only();
}
