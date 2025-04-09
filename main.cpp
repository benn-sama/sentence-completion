#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "text_utils.hpp"
#include "training_corpus/database.hpp"

using namespace std;

int main() {
    // Step 1: Load raw text from file
    string raw = loadTextFile("text.txt");
    if (raw.empty()) {
        cerr << "Error: Could not load text.txt" << endl;
        return 1;
    }

    // Step 2: Clean the text
    string cleaned = cleanText(raw);

    // Step 3: Tokenize it into words
    vector<string> words = tokenize(cleaned);
    cout << "Total words: " << words.size() << endl;

    // Step 4: Generate bigrams
    vector<pair<string, string>> bigrams = generateBigrams(words);
    cout << "Total bigrams: " << bigrams.size() << endl;

    // Step 5: Insert bigrams into the Database
    Database db;
    for (const auto& bigram : bigrams) {
        string bigramString = bigram.first + " " + bigram.second;
        db.insert(bigramString);
    }

    // Optional: Test the database
    string testWord = "to";
    cout << "Most frequent word after \"" << testWord << "\": "
         << db.retrieveNextFrequentWord(testWord) << endl;

    return 0;
}
