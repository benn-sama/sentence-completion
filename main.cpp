#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "text_utils.hpp"
#include "training_corpus/database.hpp"
#include "ngram_model.hpp"

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

    NGramModel model;
    model.train(bigrams);

    string testWord;
    cout << "Enter a word to predict the next most likely word: ";
    cin >> testWord;
    cout << endl;
    
    // Convert input to lowercase
    for (char& c : testWord) {
        c = tolower(c);
    }

    vector<pair<string, int>> predictions = db.retrieveNextNumOfFrequentWords(testWord, 2);

    if (predictions.empty()) {
        cout << "[Database] No predictions found for \"" << testWord << "\"." << endl;
    } else {
        cout << "[Database] Top predictions after \"" << testWord << "\":" << endl;
        for (int i = 0; i < predictions.size(); ++i) {
            cout << i + 1 << ". " << predictions[i].first << " (count: " << predictions[i].second << ")" << endl;
        }
    }

    vector<string> topWords = model.topNextWords(testWord, 2);

    if (topWords.empty()) {
        cout << "\n[NGramModel] No predictions found for \"" << testWord << "\"." << endl;
    } else {
        cout << "\n[NGramModel] Top predictions after \"" << testWord << "\":" << endl;
        for (int i = 0; i < topWords.size(); ++i) {
            double prob = model.getProbability(testWord, topWords[i]);
            cout << i + 1 << ". " << topWords[i] << " (probability: " << prob << ")" << endl;
        }
    }

    cout << "Total times" + testWord + "appears as a first word: " << model.getUnigramCount(testWord) << endl;

    return 0;
}
