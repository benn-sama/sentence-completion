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
    string raw = loadTextFile("1661-0.txt");
    if (raw.empty()) {
        cerr << "Error: Could not load 1661-0.txt" << endl;
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

    string testWord;
    cout << "Enter a word to predict the next most likely word: ";
    cin >> testWord;
    
    // Convert input to lowercase
    for (char& c : testWord) {
        c = tolower(c);
    }

    vector<pair<string, int>> predictions = db.retrieveNextNumOfFrequentWords(testWord, 2);

    if (predictions.empty()) {
        cout << "No predictions found for \"" << testWord << "\"." << endl;
    } else {
        cout << "Top predictions after \"" << testWord << "\":" << endl;
        for (int i = 0; i < predictions.size(); ++i) {
            cout << i + 1 << ". " << predictions[i].first << " (count: " << predictions[i].second << ")" << endl;
        }
    }

    return 0;
}
