#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream file("text.txt");
    
    if (!file) {
        cerr << "Could not open text.txt" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
    return 0;
}
