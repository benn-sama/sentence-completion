#ifndef NGRAM_MODEL_HPP
#define NGRAM_MODEL_HPP

#include "training_corpus/database.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

class NGramModel {
private:
    // Total vocabulary size (unique words)
    int vocabularySize;

    Database db;

public:
    // Constructor
    NGramModel();

    // Train the model with a list of bigrams
    void train(const std::vector<std::pair<std::string, std::string>>& bigrams);

    // Get raw bigram probability (P(w2 | w1)) using MLE
    double getProbability(const std::string& w1, const std::string& w2);

    // Get smoothed bigram probability using Laplace smoothing
    double getSmoothedProbability(const std::string& w1, const std::string& w2);

    // Predict the most likely next word after w1
    std::string predictNext(const std::string& w1);

    // Return top k likely next words
    std::vector<std::string> topNextWords(const std::string& w1, int k = 3);

    int getUnigramCount(const std::string& word);
};

#endif
