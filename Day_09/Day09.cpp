#include "../helper.hpp"


long part2(const vector<string>& input) {
    vector<vector<long>> numbers;
    for (auto l: input) {
        vector<string> line = getSubStrings(l, ' ');
        vector<long> number_line;
        for (auto s: line) number_line.push_back(stol(s));
        numbers.push_back(number_line);
    }

    long total = 0;
    for (auto line: numbers) {
        vector<long> diff_line = line;
        vector<long> differences;

        long abs_line_sum = -1;
        while (abs_line_sum != 0) {
            for (int i = 1; i < diff_line.size(); ++i) {
                diff_line[i - 1] = diff_line[i] - diff_line[i - 1];
            }
            diff_line.pop_back();
            differences.push_back(diff_line.front());

            abs_line_sum = 0;
            for (auto n: diff_line) {
                abs_line_sum += abs(n);
            }
        }

        int prev = 0;
        for (int i = differences.size() - 1; i >= 0; --i) {
            prev = differences[i] - prev;
        }

        total += line.front() - prev;
    }

    return total;
}

long part1(const vector<string>& input) {
    vector<vector<long>> numbers;
    for (auto l: input) {
        vector<string> line = getSubStrings(l, ' ');
        vector<long> number_line;
        for (auto s: line) number_line.push_back(stol(s));
        numbers.push_back(number_line);
    }

    long total = 0;
    for (auto line: numbers) {
        vector<long> diff_line = line;
        vector<long> differences;

        long abs_line_sum = -1;
        while (abs_line_sum != 0) {
            for (int i = 1; i < diff_line.size(); ++i) {
                diff_line[i - 1] = diff_line[i] - diff_line[i - 1];
            }
            diff_line.pop_back();
            differences.push_back(diff_line.back());

            abs_line_sum = 0;
            for (auto n: diff_line) {
                abs_line_sum += abs(n);
            }
        }

        long diff_sum = 0;
        for (auto d: differences) {
            diff_sum += d;
        }

        total += line.back() + diff_sum;
    }

    return total;
}

int main() {
    auto constexpr TEST = 0;
    auto constexpr TEST_FILE = "../test", INPUT_FILE = "../Day_09/input09";
    auto const filename = TEST == 1 ? TEST_FILE : INPUT_FILE;
    auto const line_count = getLineCount(filename);
    auto const input = getInput(filename, line_count);

    auto t1 = Clock::now();
    cout << part1(input); // 1980437560
    auto t2 = Clock::now();
    cout << " (" << MICRO_S(t2 - t1).count() << " μs)\n";

    t1 = Clock::now();
    cout << part2(input); // 977
    t2 = Clock::now();
    cout << " (" << MICRO_S(t2 - t1).count() << " μs)\n";
}
