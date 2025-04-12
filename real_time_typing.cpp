#include "real_time_typing.hpp"
#include "text_utils.hpp"
#include <iostream>
#include <string>
#ifdef _WIN32
    #include <conio.h>
    char getChar() { return _getch(); }
#else
    #include <termios.h>
    #include <unistd.h>
    char getChar() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif

#include <cctype>     // for isprint()
#include <algorithm>  // for all_of, find_last_of

using namespace std;

// Extracts the last word (including hyphenated) from the buffer
std::string extractLastWord(const std::string& buffer) {
    if (buffer.empty()) return "";

    size_t lastSpace = buffer.find_last_of(" ");
    std::string last = (lastSpace == std::string::npos) ? buffer : buffer.substr(lastSpace + 1);

    if (last.empty()) return "";

    int hyphenCount = std::count(last.begin(), last.end(), '-');
    if (hyphenCount > 1 || last.front() == '-' || last.back() == '-') return "";

    if (!std::all_of(last.begin(), last.end(), [](char c) {
        return std::isalpha(c) || c == '-';
    })) return "";

    return last;
}

void liveTyping(NGramModel& model) {
    string buffer;
    char ch;
    vector<string> predictions;

    cout << "\nStart typing your sentence (Press ESC to quit):\n";

    while (true) {
        ch = getChar();

        if (ch == 27) break; // ESC key
        else if (ch == '\b') {
            if (!buffer.empty()) buffer.pop_back();
        }
        else if (ch >= '1' && ch <= '3') {
            int index = ch - '1';
            if (index < predictions.size()) {
                bool endsWithSpace = !buffer.empty() && buffer.back() == ' ';

                if (endsWithSpace) {
                    // Append the selected prediction
                    buffer += predictions[index] + " ";
                } else {
                    // Replace the word being typed
                    size_t lastSpace = buffer.find_last_of(" ");
                    if (lastSpace == string::npos) {
                        buffer = predictions[index] + " ";
                    } else {
                        buffer = buffer.substr(0, lastSpace + 1) + predictions[index] + " ";
                    }
                }
            }
        }
        else if (isprint(ch)) {
            buffer += ch;
        }

        // Clear the screen for real-time effect
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "Current input: " << buffer << endl;
        cout << "Press ESC to quit.\n";

        string lowerBuffer = buffer;
        for (char& c : lowerBuffer) c = tolower(c);

        // Determine whether the user just typed a space (word completed)
        bool endsWithSpace = !lowerBuffer.empty() && lowerBuffer.back() == ' ';
        string lastWord = "";

        vector<string> tokens = tokenize(lowerBuffer);
        if (endsWithSpace && !tokens.empty()) {
            lastWord = tokens.back(); // use last full word before space
        } else {
            lastWord = extractLastWord(lowerBuffer); // still typing a word
        }

        predictions = model.topNextWords(lastWord, 3);

        if (!lastWord.empty() && !predictions.empty()) {
            cout << "\nPredicted next words (after \"" << lastWord << "\"):\n";
            for (int i = 0; i < predictions.size(); ++i) {
                double prob = model.getProbability(lastWord, predictions[i]);
                cout << (i + 1) << ". " << predictions[i] << " (p = " << prob << ")\n";
            }
            cout << "(Press 1-3 to insert a prediction)\n";
        }
    }

    cout << "\nFinal sentence: " << buffer << endl;
}
