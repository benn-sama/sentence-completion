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

    To insert a given string, call insert(std::string sentence).
      STRONG ENCOURAGED: A two word string should be passed rather than a single word string.
      The insert() method automatically adds +1 or adds the word to their corresponding hashtable.
      Example: 
        1. (RECOMMENDED) 
          insert("machine learning"), will add "machine" into the singleWord hashtable, then "learning" will also be added to the doubleWord hashtable
          automatically. 

        2. (USE ONLY WHEN NEEDED)
          insert("machine learning") && insert("machine"), this causes machine to have an extra +1 in the singleWord hashtable or how ever many times you insert it by itself.

  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    To retrieve the count of a specific word, call returnFirstWordCount(std::string sentence).
      Example: 
        To get the count of the word "machine", call
        returnFirstWordCount("machine");
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    To retrieve the next most frequent word after a given word, call returnMostFrequentSecondWord(std::string word).
      Example: 
        To get the word that is next in frequency after "machine", call
        returnMostFrequentSecondWord("machine");
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    To retrieve the count of the next most frequent word after a given word, call returnSecondWordCount(std::string firstWord, std::string secondWord).
      Example: 
        To get the count of the next most frequent word after "machine", call
        returnSecondWordCount("machine", retrieveNextFrequentWord("machine"));
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    To retrieve multiple highest frequency words from the doubleWord hashtable, call returnMultipleSecondWords(std::string word, int numOfWords).
    This will return a vector of pairs, string:int (string and it's corresponding int) of the highest int. If there is NOT enough pairs to return, then
    it will return how ever many pairs it has in the vector.
      Example:
        To get 5 highest frequency second words for "machine", call
        returnMultipleSecondWords("machine", 5);
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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