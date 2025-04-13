void testing_empty_database();
void testing_single_words_only();
void testing_two_words_only();
void testing_both_words_simultaneously();
void testing_returning_most_frequent_second_word();
void testing_return_multiple_second_words();
void testing_arbitrary_strings();

void testTraining();
void testProbabilities();
void testPrediction();
void testSpecificProbabilities();


int main() {
  testing_empty_database();
  testing_single_words_only();
  testing_two_words_only();
  testing_both_words_simultaneously();
  testing_returning_most_frequent_second_word();
  testing_return_multiple_second_words();

  testing_arbitrary_strings();

  testTraining();
  testProbabilities();
  testPrediction();
  testSpecificProbabilities();
  return 0;
}