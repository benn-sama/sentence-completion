#include "ngram_model.hpp"
#include <algorithm> // for std::max_element
#include <numeric>   // for std::accumulate

// Constructor
NGramModel::NGramModel() {
  vocabularySize = 0;
  db = Database(1000);
}

// Train the model with bigram pairs
void NGramModel::train(const std::vector<std::pair<std::string, std::string>>& bigrams) {
  for (const auto& pair : bigrams) {
    const std::string& w1 = pair.first;
    const std::string& w2 = pair.second;

    db.insert(w1 + " " + w2);
}

vocabularySize = db.returnVocabSize();
}

// Maximum Likelihood Estimation: P(w2 | w1) = Count(w1, w2) / Count(w1)
double NGramModel::getProbability(const std::string& w1, const std::string& w2) {
  if (db.returnFirstWordCount(w1) <= 0) return 0.0;

    int bigramCount = db.returnSecondWordCount(w1, w2);
    int unigramCount = db.returnFirstWordCount(w1);

    if (unigramCount == 0) return 0.0;
    return static_cast<double>(bigramCount) / unigramCount;
}

// Laplace Smoothing: P(w2 | w1) = (Count(w1, w2) + 1) / (Count(w1) + V)
double NGramModel::getSmoothedProbability(const std::string& w1, const std::string& w2) {
  int bigramCount = db.returnSecondWordCount(w1, w2);
  int unigramCount = db.returnFirstWordCount(w1);

  return static_cast<double>(bigramCount + 1) / (unigramCount + vocabularySize);
}

// Predict the most likely next word after w1
std::string NGramModel::predictNext(const std::string& w1) {
  if (bigramCounts.find(w1) == bigramCounts.end()) return "?";

  return db.returnMostFrequentSecondWord(w1);
}

// Return top K most frequent next words
std::vector<std::string> NGramModel::topNextWords(const std::string& w1, int k) {
  std::vector<std::string> result;
  std::vector<std::pair<std::string, int>> words = db.returnMultipleSecondWords(w1, k);
  
  if (words.size() <= 0) {
    return result;
  }

  for (size_t i = 0; i < words.size(); ++i) {
    result.push_back(words.at(i).first);
  }

  return result;
}

int NGramModel::getUnigramCount(const std::string& word) {
  return db.returnFirstWordCount(word);
}