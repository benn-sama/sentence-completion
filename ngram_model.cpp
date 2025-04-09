#include "ngram_model.hpp"
#include <algorithm> // for std::max_element
#include <numeric>   // for std::accumulate

// Constructor
NGramModel::NGramModel() {
  vocabularySize = 0;
}

// Train the model with bigram pairs
void NGramModel::train(const std::vector<std::pair<std::string, std::string>>& bigrams) {
  for (const auto& pair : bigrams) {
    const std::string& w1 = pair.first;
    const std::string& w2 = pair.second;

    bigramCounts[w1][w2]++;
    unigramCounts[w1]++;

    // Make sure w2 is in the unigram count map too (for vocab size)
    if (unigramCounts.find(w2) == unigramCounts.end()) {
        unigramCounts[w2] = 0;
    }
}

vocabularySize = unigramCounts.size();
}

// Maximum Likelihood Estimation: P(w2 | w1) = Count(w1, w2) / Count(w1)
double NGramModel::getProbability(const std::string& w1, const std::string& w2) {
  if (unigramCounts.find(w1) == unigramCounts.end()) return 0.0;

    int bigramCount = bigramCounts[w1][w2];
    int unigramCount = unigramCounts[w1];

    if (unigramCount == 0) return 0.0;
    return static_cast<double>(bigramCount) / unigramCount;
}

// Laplace Smoothing: P(w2 | w1) = (Count(w1, w2) + 1) / (Count(w1) + V)
double NGramModel::getSmoothedProbability(const std::string& w1, const std::string& w2) {
  int bigramCount = bigramCounts[w1][w2];
  int unigramCount = unigramCounts[w1];

  return static_cast<double>(bigramCount + 1) / (unigramCount + vocabularySize);
}

// Predict the most likely next word after w1
std::string NGramModel::predictNext(const std::string& w1) {
  if (bigramCounts.find(w1) == bigramCounts.end()) return "?";

    const auto& nextWords = bigramCounts[w1];
    std::string bestWord = "?";
    double maxProb = 0.0;

    for (const auto& pair : nextWords) {
        double prob = getProbability(w1, pair.first);
        if (prob > maxProb) {
            maxProb = prob;
            bestWord = pair.first;
        }
    }

    return bestWord;
}

// Return top K most frequent next words
std::vector<std::string> NGramModel::topNextWords(const std::string& w1, int k) {
  std::vector<std::string> result;

    if (bigramCounts.find(w1) == bigramCounts.end()) return result;

    std::vector<std::pair<std::string, double>> wordProbs;

    for (const auto& pair : bigramCounts[w1]) {
        double prob = getProbability(w1, pair.first);
        wordProbs.push_back({ pair.first, prob });
    }

    // Sort descending by probability
    std::sort(wordProbs.begin(), wordProbs.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    for (int i = 0; i < k && i < wordProbs.size(); ++i) {
        result.push_back(wordProbs[i].first);
    }

    return result;
}