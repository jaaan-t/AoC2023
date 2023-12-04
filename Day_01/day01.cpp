#include "../helper.hpp"

#include <regex>

using std::regex;

void part1(const vector<string>& input) {
    int total = 0;
    for (const string& s: input) {
        int length = int(s.length());
        int first = -1;
        int last = -1;
        for (int i = 0; i < length; ++i) {
            if (isdigit(s[i])) {
                if (first == -1) first = i;
                if (i >= first) last = i;
            }
        }
        stringstream stream;
        stream << s[first] - '0' << s[last] - '0';
        int number = stoi(stream.str());
        total += number;
    }
    cout << total << "\n";
}

string findReplace(const string& s, const string& f, const string& r) {
    return regex_replace(s, std::regex(f), r);
}

void part2(vector<string>& input) {
    for (string& s: input) {
        s = findReplace(s, "one", "o1e");
        s = findReplace(s, "two", "t2o");
        s = findReplace(s, "three", "th3ee");
        s = findReplace(s, "four", "f4ur");
        s = findReplace(s, "five", "f5ve");
        s = findReplace(s, "six", "s6x");
        s = findReplace(s, "seven", "se7en");
        s = findReplace(s, "eight", "ei8ht");
        s = findReplace(s, "nine", "n9ne");
        s = findReplace(s, "zero", "z0ro");
    }
}

int main() {
    string filename = "input01";
    int lineCount = getLineCount(filename);
    vector<string> input = getInput(filename, lineCount);

    auto t1 = Clock::now();
    part1(input); // 54634
    auto t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs" << "\n";

    t1 = Clock::now();
    part2(input);
    part1(input); // 53855
    t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs" << "\n";
}
