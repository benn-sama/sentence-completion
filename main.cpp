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
    int user = -1;
    cout << "1. For casual texting dataset.\n2. For book writing dataset.\n";
    cout << "Input: ";
    cin >> user;

    while (user < 1 || user > 2 || cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input...\n";
        cout << "1. For casual texting dataset.\n2. For book writing dataset.\n";
        cout << "Input: ";
        cin >> user;
    }

    string raw = "";
    if (user == 1) {
        raw = loadTextFile("dialog.txt");
    }
    else {
        raw = loadTextFile("1661-0.txt");
    }

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
