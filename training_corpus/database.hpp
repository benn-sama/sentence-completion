#ifndef DATABASE_HPP
#define DATABASE_HPP

/*
  Training Corpus Database

  This class is responsible for storing the total count of both single-word and two-word appearances
  within a corpus. It uses a hashtable for efficient lookup and storage.

  Constructor:
    Database(int bucketCount);

  Description:
    - Constructs a Database object with a specified number of memory buckets.
    - Preallocating memory buckets is **RECOMMENDED** to avoid hashtable resizing,
      which has a time complexity of O(n).

  Guide:
  To interact with word frequencies, use the following functions:

  To retrieve the count of a specific word, call retrieveSingleWordCount(std::string sentence).
  Example: To get the count of the word "machine", call
  retrieveSingleWordCount("machine");

  To retrieve the next most frequent word after a given word, call retrieveNextFrequentWord(std::string word).
  Example: To get the word that is next in frequency after "machine", call
  retrieveNextFrequentWord("machine");

  To retrieve the count of the next most frequent word after a given word, call retrieveNextWordCount(std::string firstWord, std::string secondWord).
  Example: To get the count of the next most frequent word after "machine", call
  retrieveNextWordCount("machine", retrieveNextFrequentWord("machine"));
*/


#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

class Database {
  private:
    std::unordered_map<std::string, int> singleWord; // stores single words
    std::unordered_map<std::string, std::unordered_map<std::string, int>> doubleWord; // stores double words
    
    bool insertOneWord(std::string word);
    bool insertTwoWord(std::string firstWord, std::string secondWord);
  public:
    Database() {};
    Database(int reserveCount) { singleWord.reserve(reserveCount); doubleWord.reserve(reserveCount); }
    void insert(std::string sentence);  // inserts string based on whether it is a one word or a two word
    int returnFirstWordCount(std::string word); // retrieves the highest count of the word
    int returnSecondWordCount(std::string firstWord, std::string secondWord); 
    std::string returnMostFrequentSecondWord(std::string word); // retrieves the highest count of the next word
    std::vector<std::pair<std::string, int>> returnMultipleSecondWords(std::string word, int numOfWords); // returns a vector of the string and associated int
};

#endif