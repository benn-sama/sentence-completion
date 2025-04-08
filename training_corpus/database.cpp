#include "database.hpp"

bool Database::insertOneWord(std::string word) { // method for inserting a one word string
  if (word.empty()) {
    return false;
  }

  singleWord[word]++;

  return true;
}

bool Database::insertTwoWord(std::string firstWord, std::string secondWord) { // method for inserting a two word string
  if (secondWord.empty()) {
    return false;
  }

  doubleWord[firstWord][secondWord]++;
  return true;
}

void Database::insert(std::string sentence) { // inserts two word string
  std::istringstream stream(sentence);
  std::string firstWord = "";
  std::string secondWord = "";

  stream >> firstWord >> secondWord;

  if (!this->insertOneWord(sentence)) {
    return;
  }

  if (!this->insertTwoWord(firstWord, secondWord)) {
    return;
  }
}

int Database::retrieveSingleWordCount(std::string word) { // returns total string appearance or returns -1
  std::istringstream stream(word);
  std::string firstWord = "";
  std::string secondWord = "";

  stream >> firstWord >> secondWord;

  if (firstWord.empty()) {
    return -1;
  }

  if (secondWord.empty()) {
    return singleWord[firstWord];
  }
  else {
    return -1;
  }
}

int Database::retrieveNextWordCount(std::string firstWord, std::string secondWord) {
  if (firstWord.empty() || secondWord.empty()) {
    return -1;
  }

  return doubleWord[firstWord][secondWord];
}

std::string Database::retrieveNextFrequentWord(std::string word) { // retrieves the highest next word
  std::unordered_map<std::string, std::unordered_map<std::string, int>>::const_iterator outerTable;
  outerTable = doubleWord.find(word);

  
  if (outerTable == doubleWord.end()) {
    return "";
  }

  std::unordered_map<std::string, int>::const_iterator innerTable;
  int max = 0;
  std::string nextWord = "";
  for (innerTable = outerTable->second.begin(); innerTable != outerTable->second.end(); ++innerTable) {
    if (innerTable->second > max) {
      max = innerTable->second;
      nextWord = innerTable->first;
    }
  }

  return nextWord;
}

