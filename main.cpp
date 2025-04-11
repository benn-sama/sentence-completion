#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cctype>
#include "text_utils.hpp"
#include "training_corpus/database.hpp"
#include "ngram_model.hpp"
#include "real_time_typing.hpp"

using namespace std;

int main() {
    // Load and preprocess
    string raw = loadTextFile("1661-0.txt");
    if (raw.empty()) {
        cerr << "Error: Could not load 1661-0.txt" << endl;
        return 1;
    }

    string cleaned = cleanText(raw);
    vector<string> words = tokenize(cleaned);
    vector<pair<string, string>> bigrams = generateBigrams(words);

    // Train model
    NGramModel model;
    model.train(bigrams);

    // Launch real-time typing
    liveTyping(model);

    return 0;
}
