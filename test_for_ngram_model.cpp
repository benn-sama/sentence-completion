#include <iostream>
#include <vector>
#include "ngram_model.hpp"

using namespace std;

void test_basic_probability() {
    cout << "\n[TEST] Basic Training + MLE + Laplace\n";

    NGramModel model;
    vector<pair<string, string>> bigrams = {
        {"i", "have"},
        {"i", "have"},
        {"i", "was"},
        {"sherlock", "holmes"},
        {"sherlock", "holmes"},
        {"sherlock", "watson"},
    };

    model.train(bigrams);

    double mle = model.getProbability("i", "have");
    double laplace = model.getSmoothedProbability("i", "have");

    cout << "P(have | i) MLE = " << mle << endl;
    cout << "P(have | i) Laplace = " << laplace << endl;

    cout << "predictNext(\"sherlock\") = " << model.predictNext("sherlock") << endl;

    vector<string> topWords = model.topNextWords("sherlock", 2);
    for (int i = 0; i < topWords.size(); ++i) {
        cout << i + 1 << ". " << topWords[i] << " (MLE: "
             << model.getProbability("sherlock", topWords[i]) << ", Laplace: "
             << model.getSmoothedProbability("sherlock", topWords[i]) << ")" << endl;
    }
}

int main() {
    test_basic_probability();
    return 0;
}
