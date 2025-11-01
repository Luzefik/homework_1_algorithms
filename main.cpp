#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <iostream>

using namespace std;


void readFile(const string &fileName) {
    // Try opening with ifstream for read-only
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Failed to open file '" << fileName << "'.\n";
        // Print current working directory to help debug relative path issues
        // Try to print POSIX current working directory to help debug relative path issues
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            cerr << "Current working directory: " << cwd << '\n';
        } else {
            cerr << "(Could not determine current path)\n";
        }
        return;
    }

    string line;
    size_t lineNo = 0;
    while (getline(file, line)) {
        ++lineNo;
        // Print each line so user sees progress and that file was opened
        cout << lineNo << ": " << line << '\n';
    }
}

int main() {
    readFile("students.csv");
    return 0;
}