#include "ngram_model.hpp"
#include <algorithm> // for std::max_element
#include <numeric>   // for std::accumulate

// Constructor
NGramModel::NGramModel() {
  vocabularySize = 0;
}

// Train the model with bigram pairs
void NGramModel::train(const std::vector<std::pair<std::string, std::string>>& bigrams) {

}

// Maximum Likelihood Estimation: P(w2 | w1) = Count(w1, w2) / Count(w1)
double NGramModel::getProbability(const std::string& w1, const std::string& w2) {

}

// Laplace Smoothing: P(w2 | w1) = (Count(w1, w2) + 1) / (Count(w1) + V)
double NGramModel::getSmoothedProbability(const std::string& w1, const std::string& w2) {

}

// Predict the most likely next word after w1
std::string NGramModel::predictNext(const std::string& w1) {

}

// Return top K most frequent next words
std::vector<std::string> NGramModel::topNextWords(const std::string& w1, int k) {

}