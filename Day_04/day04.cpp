#include "../helper.hpp"

#include <queue>

int part1(const vector<string>& input, vector<int>& cards) {
    int total = 0;

    const vector<string> top = getSubStrings(input[0], ' ');
    const int size = static_cast<int>(top.size());
    int sep = 0;
    for (int i = 0; i < size; ++i) {
        if (top[i] == "|") sep = i;
    }
    const int num_numbers = sep - 2;
    const int num_winning = size - sep - 1;

    for (int i = 0; i < input.size(); ++i) {
        int card = 0;
        vector<string> substr = getSubStrings(input[i], ' ');
        vector<int> numbers(num_numbers);
        vector<int> winning(num_winning);
        for (int j = 2; j < sep; ++j) {
            numbers[j - 2] = stoi(substr[j]);
        }
        for (int j = sep + 1; j < size; ++j) {
            winning[j - sep - 1] = stoi(substr[j]);
        }
        for (const int n: numbers) {
            for (const int w: winning) {
                if (n == w) {
                    card += 1;
                    break;
                }
            }
        }
        cards[i] = card;
        total += card > 0 ? static_cast<int>(pow(2, card - 1)) : 0;
    }

    return total;
}

int part2(const vector<int>& cards) {
    int total = 0;

    std::queue<int> q;
    for (int i = 0; i < cards.size(); ++i) {
        q.push(i);
    }

    while (!q.empty()) {
        const int idx = q.front();
        const int nxt = cards[idx];
        for (int i = idx + 1; i <= idx + nxt; ++i) {
            q.push(i);
        }
        ++total;
        q.pop();
    }

    return total;
}

int main() {
    auto const filename = "input04";
    auto const lineCount = getLineCount(filename);
    auto const input = getInput(filename, lineCount);

    vector<int> cards(lineCount);

    auto t1 = Clock::now();
    cout << part1(input, cards) << " ("; // 15268
    auto t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms)\n";

    t1 = Clock::now();
    cout << part2(cards) << " ("; // 6283755
    t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms)\n";
}
