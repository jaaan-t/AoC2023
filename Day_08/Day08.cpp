#include "../helper.hpp"
#include <map>

using std::map;

struct Node {
    string name;
    string left;
    string right;
};

inline std::ostream& operator<<(std::ostream& stream, const Node& node) {
    stream << node.name << "-" << node.left << "-" << node.right;
    return stream;
}

int part2(const vector<string>& input) {
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

    int steps = 0;
    vector<Node> next_nodes = starting_nodes;
    string dir = input[0];
    bool finished = false;
    while (!finished) {
        for (char c: dir) {
            ++steps;
            if (steps % 10000000 == 0) cout << steps << "\n";
            for (size_t i = 0; i < next_nodes.size(); ++i) {
                if (c == 'L') {
                    next_nodes[i] = graph.at(next_nodes[i].left);
                }
                if (c == 'R') {
                    next_nodes[i] = graph.at(next_nodes[i].right);
                }
            }
        }

        finished = true;
        for (Node n: next_nodes) {
            if (n.name[2] != 'Z') {
                finished = false;
                break;
            }
        }
    }

    return steps;
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
