#include <iostream>
#include <fstream>
#include <string>
#include "text_utils.hpp"

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

    // Optional: Print first 5 bigrams
    for (int i = 0; i < 5 && i < bigrams.size(); ++i) {
        cout << bigrams[i].first << " " << bigrams[i].second << endl;
    }

    return 0;
}
