#include "../helper.hpp"


int64_t getWins(const int64_t t, const int64_t d) {
    int64_t wins = 0;
    for (int64_t i = 1; i < t - 1; ++i) {
        const int64_t dist = (t - i) * i;
        if (dist > d) wins += 1;
    }
    return wins;
}

int64_t part2(const vector<string>& input) {
    const vector<string> line1 = getSubStrings(input[0], ' ');
    stringstream stream1;
    for (int i = 1; i < line1.size(); ++i) {
        stream1 << line1[i];
    }

    const vector<string> line2 = getSubStrings(input[1], ' ');
    stringstream stream2;
    for (int i = 1; i < line2.size(); ++i) {
        stream2 << line2[i];
    }

    return getWins(stol(stream1.str()), stol(stream2.str()));
}

int64_t part1(const vector<string>& input) {
    const vector<string> line1 = getSubStrings(input[0], ' ');
    const vector<string> line2 = getSubStrings(input[1], ' ');
    vector<int64_t> time;
    for (int64_t i = 1; i < line1.size(); ++i) {
        time.push_back(stol(line1[i]));
    }
    vector<int64_t> dist;
    for (int64_t i = 1; i < line2.size(); ++i) {
        dist.push_back(stol(line2[i]));
    }

    int64_t wins = 1;
    for (int64_t i = 0; i < time.size(); ++i) {
        wins *= getWins(time[i], dist[i]);
    }
    return wins;
}

int main() {
    auto constexpr TEST = 0;
    auto constexpr TEST_FILE = "../test", INPUT_FILE = "input06";
    auto const filename = TEST == 1 ? TEST_FILE : INPUT_FILE;
    auto const line_count = getLineCount(filename);
    auto const input = getInput(filename, line_count);

    auto t1 = Clock::now();
    cout << part1(input); // 2344708
    auto t2 = Clock::now();
    cout << " (" << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs)\n";

    t1 = Clock::now();
    cout << part2(input); // 30125202
    t2 = Clock::now();
    cout << " (" << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms)\n";
}
