#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cctype>
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

    string currentWord;
    string sentence;

    while (true) {
        cout << "\nCurrent sentence: " << sentence << endl;
        cout << "Enter a word, or choose a suggestion (1/2), or type 'exit' to quit: ";
    
        string input;
        cin >> input;
    
        if (input == "exit") break;
    
        // Suggestion selection
        if ((input == "1" || input == "2") && !currentWord.empty()) {
            int choice = stoi(input) - 1;
            vector<string> suggestions = model.topNextWords(currentWord, 2);
    
            if (choice < suggestions.size()) {
                string chosenWord = suggestions[choice];
                sentence += " " + chosenWord;
                currentWord = chosenWord;
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
        
        // Accept input if it's a valid word or single hyphenated 
        // word (e.g., "long-term"), but reject if it starts/ends with hyphen or has multiple
        else if (
            count(input.begin(), input.end(), '-') <= 1 &&
            input.front() != '-' && input.back() != '-' &&
            all_of(input.begin(), input.end(), [](char c) {
                return isalpha(c) || c == '-';
            })
        ) {
            for (char& c : input) c = tolower(c);
            sentence += (sentence.empty() ? "" : " ") + input;
            currentWord = input;
        }
        else {
            // Reject anything that's not a letter or suggestion
            cout << "Invalid input. Please enter a word or choose 1/2.\n";
            continue;
        }
    
        // Show predictions
        vector<string> topWords = model.topNextWords(currentWord, 2);
        if (topWords.empty()) {
            cout << "[NGramModel] No predictions found for \"" << currentWord << "\"." << endl;
        } else {
            cout << "[NGramModel] Top suggestions:\n";
            for (int i = 0; i < topWords.size(); ++i) {
                double prob = model.getProbability(currentWord, topWords[i]);
                cout << "(" << i + 1 << ") " << topWords[i] << " (p = " << prob << ")";
                if (i == 0 && topWords.size() > 1) cout << "\n                or\n";
                else cout << "\n";
            }
        }
    }

    cout << "\nFinal completed sentence: " << sentence << endl;

    return 0;
}
