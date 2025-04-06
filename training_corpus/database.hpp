#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <unordered_map>
#include <string>
#include <sstream>

class Database {
  private:
    std::unordered_map<std::string, int> singleWord; // stores single words
    std::unordered_map<std::string, int> doubleWord; // stores double words
    
    bool insertOneWord(std::string word);
    bool insertTwoWord(std::string word, std::string sentence);
  public:
    Database() {};
    Database(int reserveCount) { singleWord.reserve(reserveCount); doubleWord.reserve(reserveCount); }
    void insert(std::string sentence);  // inserts string based on whether it is a one word or a two word
    int retrieve(std::string sentence); // retrieves string
};

#endif