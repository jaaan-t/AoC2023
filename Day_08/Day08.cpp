#include "../helper.hpp"
#include <map>
#include <numeric>

using std::map;
using std::lcm;

struct Node {
    string name;
    string left;
    string right;
};

inline std::ostream& operator<<(std::ostream& stream, const Node& node) {
    stream << node.name << "-" << node.left << "-" << node.right;
    return stream;
}

long part2(const vector<string>& input) {
    std::map<string, Node> graph;
    for (int i = 2; i < input.size(); ++i) {
        auto sub = getSubStrings(input[i], ' ');
        Node node{sub[0], sub[2].substr(1, 3), sub[3].substr(0, 3)};
        graph.insert(std::pair{node.name, node});
    }

    vector<Node> starting_nodes;
    for (auto p: graph) {
        if (p.first[2] == 'A') {
            starting_nodes.push_back(p.second);
        }
    }

    vector<Node> next_nodes = starting_nodes;
    string dir = input[0];
    vector<long> steps_list;
    for (int i = 0; i < next_nodes.size(); ++i) {
        int step = 0;
        while (true) {
            for (char c: dir) {
                ++step;
                if (c == 'L') next_nodes[i] = graph.at(next_nodes[i].left);
                if (c == 'R') next_nodes[i] = graph.at(next_nodes[i].right);
            }
            if (next_nodes[i].name[2] == 'Z') {
                steps_list.push_back(step);
                break;
            }
        }
    }

    long steps_total = steps_list[0];
    for (size_t i = 1; i < steps_list.size(); ++i) {
        steps_total = lcm(steps_total, steps_list[i]);
    }

    return steps_total;
}

int part1(const vector<string>& input) {
    std::map<string, Node> graph;
    for (int i = 2; i < input.size(); ++i) {
        auto sub = getSubStrings(input[i], ' ');
        Node node{sub[0], sub[2].substr(1, 3), sub[3].substr(0, 3)};
        graph.insert(std::pair{node.name, node});
    }

    string dir = input[0];
    Node n = graph.at("AAA");
    int steps = 0;
    while (true) {
        for (auto c: dir) {
            ++steps;
            if (c == 'L') {
                n = graph.at(n.left);
                if (n.name == "ZZZ") return steps;
            }
            if (c == 'R') {
                n = graph.at(n.right);
                if (n.name == "ZZZ") return steps;
            }
        }
    }
}

int main() {
    auto constexpr TEST = 0;
    auto constexpr TEST_FILE = "../test", INPUT_FILE = "../Day_08/input08";
    auto const filename = TEST == 1 ? TEST_FILE : INPUT_FILE;
    auto const line_count = getLineCount(filename);
    auto const input = getInput(filename, line_count);

    auto t1 = Clock::now();
    cout << part1(input); // 19637
    auto t2 = Clock::now();
    cout << " (" << MILLI_S(t2 - t1).count() << " ms)\n";

    t1 = Clock::now();
    cout << part2(input);
    t2 = Clock::now();
    cout << " (" << MILLI_S(t2 - t1).count() << " ms)\n";
}
