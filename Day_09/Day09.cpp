#include "../helper.hpp"


int part2(const vector<string>& input) {

    return 0;
}

int part1(const vector<string>& input) {

    return 0;
}

int main() {
    auto constexpr TEST = 0;
    auto constexpr TEST_FILE = "../test", INPUT_FILE = "input09";
    auto const filename = TEST == 1 ? TEST_FILE : INPUT_FILE;
    auto const line_count = getLineCount(filename);
    auto const input = getInput(filename, line_count);

    // auto t1 = Clock::now();
    cout << part1(input);
    // auto t2 = Clock::now();
    // cout << " (" << MICRO_S(t2 - t1).count() << " μs)\n";

    // t1 = Clock::now();
    cout << part2(input);
    // t2 = Clock::now();
    // cout << " (" << MICRO_S(t2 - t1).count() << " μs)\n";
}
