#include "database.hpp"

bool Database::insertOneWord(std::string word) { // method for inserting a one word string
  if (word.empty()) {
    return false;
  }

  if (singleWord.find(word) != singleWord.end()) {
    singleWord[word] += 1;
  }
  else {
    singleWord[word] = 1;
  }

  return true;
}

bool Database::insertTwoWord(std::string word, std::string sentence) { // method for inserting a two word string
  if (word.empty()) {
    return false;
  }

  if (doubleWord.find(sentence) != doubleWord.end()) {
    doubleWord[sentence] += 1;
  }
  else {
    doubleWord[sentence] = 1;
  }  

  return true;
}

void Database::insert(std::string sentence) { // inserts string
  std::istringstream stream(sentence);
  std::string firstWord = "";
  std::string secondWord = "";

  stream >> firstWord >> secondWord;

  if (!this->insertOneWord(sentence)) {
    return;
  }

  if (!this->insertTwoWord(secondWord, sentence)) {
    return;
  }
}

int Database::retrieve(std::string sentence) { // returns total string appearance or returns -1
  if (singleWord.find(sentence) != singleWord.end()) {
    return singleWord[sentence];
  }

  if (doubleWord.find(sentence) != doubleWord.end()) {
    return doubleWord[sentence];
  }

  return -1;
}

