#include "../database.hpp"

#include <iostream>

void testing_empty_database() {
  Database db(10);

  if (db.retrieveSingleWordCount("") != -1) {
    std::cerr << "FAIL: retrieveSingleWordCount()\n Does not return -1 after a empty parameter";
  }
}

void testing_single_words_only() {

}

void testing_two_words_only() {

}

void testing_both_words_simultaneously() {

}

int main() {
  testing_empty_database();
}