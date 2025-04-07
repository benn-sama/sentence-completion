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
*/


#include <unordered_map>
#include <string>
#include <sstream>

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
    int retrieveCount(std::string sentence); // retrieves string
    std::string retrieveNextWord(std::string word); // retrieves the next word
};

#endif