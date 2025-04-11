#include <iostream>
#include <vector>
#include "ngram_model.hpp"

using namespace std;

// This function tests:
// - MLE (Maximum Likelihood Estimation)
// - Laplace Smoothing
// - Predicting the next word
// - Getting the top N likely next words
void test_basic_probability() {
    cout << "\n[TEST] Basic Training + MLE + Laplace\n";

    // Create a new NGramModel instance
    NGramModel model;

    // Provide a small, known training set of bigrams
    // "i have" appears 2 times
    // "i was" appears 1 time
    // "sherlock holmes" appears 2 times
    // "sherlock watson" appears 1 time
    vector<pair<string, string>> bigrams = {
        {"i", "have"},
        {"i", "have"},
        {"i", "was"},
        {"sherlock", "holmes"},
        {"sherlock", "holmes"},
        {"sherlock", "watson"},
    };

    // Train the model with the bigrams above
    model.train(bigrams);

    // Get the MLE (raw frequency probability) of "have" given "i"
    double mle = model.getProbability("i", "have");

    // Get the Laplace-smoothed probability of "have" given "i"
    double laplace = model.getSmoothedProbability("i", "have");

    // Print both probabilities
    cout << "P(have | i) MLE = " << mle << endl;
    cout << "P(have | i) Laplace = " << laplace << endl;

    // Test which word the model thinks is most likely after "sherlock"
    cout << "predictNext(\"sherlock\") = " << model.predictNext("sherlock") << endl;

    // Get the top 2 most likely next words after "sherlock"
    vector<string> topWords = model.topNextWords("sherlock", 2);

    // Print each top word along with both its MLE and Laplace probability
    for (int i = 0; i < topWords.size(); ++i) {
        cout << i + 1 << ". " << topWords[i] << " (MLE: "
             << model.getProbability("sherlock", topWords[i]) << ", Laplace: "
             << model.getSmoothedProbability("sherlock", topWords[i]) << ")" << endl;
    }
}

// Entry point: run the test
int main() {
    test_basic_probability();
    return 0;
}
