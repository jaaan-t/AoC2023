#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

#define MILLI_S std::chrono::duration_cast<std::chrono::milliseconds>
#define MICRO_S std::chrono::duration_cast<std::chrono::microseconds>

using std::cout;
using std::vector;
using std::string;
using std::ifstream;
using std::stringstream;
using std::stoi;
using Clock = std::chrono::high_resolution_clock;

inline size_t stringToSize_T(const string& s) {
    stringstream stream(s);
    size_t output;
    stream >> output;
    return output;
}

inline bool isNumber(const string& s) {
    return std::ranges::all_of(s, [](const char c) { return isdigit(c); });
}

inline vector<string> getSubStrings(const string& line, const char dlm) {
    vector<string> subStrings;
    stringstream stream(line);
    while (stream.good()) {
        string substr;
        getline(stream, substr, dlm);
        if (!substr.empty())
            subStrings.push_back(substr);
    }
    return subStrings;
}

inline int getLineCount(const string& filename) {
    int lineCount = 0;

    if (ifstream file(filename); file.is_open()) {
        string line;
        while (getline(file, line))
            ++lineCount;
        file.close();
    } else cout << "Unable to open file";

    return lineCount;
}

inline vector<string> getInput(const string& filename, const int lineCount) {
    vector<string> input(lineCount, "");

    if (ifstream file(filename); file.is_open()) {
        string line;
        int pos = 0;
        while (getline(file, line)) {
            input[pos] = line;
            pos++;
        }
        file.close();
    } else cout << "Unable to open file";

    return input;
}
