#include "real_time_typing.hpp"
#include "text_utils.hpp"
#include <iostream>
#include <string>
#include <conio.h>  // for _getch()
#include <cctype>   // for isprint()

using namespace std;

void liveTyping(NGramModel& model) {
  string buffer;
  char ch;
  vector<string> predictions;

  cout << "\nStart typing your sentence (Press ESC to quit):\n";

  while (true) {
      ch = _getch();

      if (ch == 27) break; // ESC key

      else if (ch == '\b') { // Backspace
          if (!buffer.empty()) buffer.pop_back();
      }

      // Check for suggestion selection: 1, 2, or 3
      else if (ch >= '1' && ch <= '3') {
          int index = ch - '1';
          if (index < predictions.size()) {
              // Remove current word being typed
              size_t lastSpace = buffer.find_last_of(" ");
              if (lastSpace == string::npos) {
                  buffer = predictions[index] + " ";  // replace whole buffer
              } else {
                  buffer = buffer.substr(0, lastSpace + 1) + predictions[index] + " "; // replace last word
              }
          }
      }

      else if (isprint(ch)) {
          buffer += ch;
      }

      // Clear the screen
      system("cls");

      cout << "Current input: " << buffer << endl;
      cout << "Press ESC to quit.\n";

      // Get last word
      string lastWord = "";
      string lowerBuffer = buffer;
      for (char& c : lowerBuffer) c = tolower(c);
      auto tokens = tokenize(lowerBuffer);
      if (!tokens.empty()) lastWord = tokens.back();

      // Get predictions
      predictions = model.topNextWords(lastWord, 3);

      if (!lastWord.empty() && !predictions.empty()) {
          cout << "\nPredicted next words:\n";
          for (int i = 0; i < predictions.size(); ++i) {
              double prob = model.getProbability(lastWord, predictions[i]);
              cout << (i + 1) << ". " << predictions[i] << " (p = " << prob << ")\n";
          }
          cout << "(Press 1-3 to insert a prediction)\n";
      }
  }

  cout << "\nFinal sentence: " << buffer << endl;
}
