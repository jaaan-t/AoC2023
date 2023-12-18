#include "../helper.hpp"

vector<string> getSubStrings(const vector<string>& input, char dlm, const string& exclude) {
    vector<string> subStrings;
    for (const string& line: input) {
        stringstream stream(line);
        while (stream.good()) {
            string substr;
            getline(stream, substr, dlm);
            if (substr.find(exclude) != 0 && !substr.empty())
                subStrings.push_back(substr);
        }
    }
    return subStrings;
}

void part1(const vector<string>& input, int redMax, int greenMax, int blueMax) {
    int total = 0;
    int id = 0;
    vector<string> games = getSubStrings(input, ':', "Game");
    for (const string& g: games) {
        bool possible = true;
        id += 1;
        vector<string> game = getSubStrings(g, ';');

        for (const string& s: game) {
            vector<string> grab = getSubStrings(s, ',');
            for (const string& gr: grab) {
                vector<string> cubes = getSubStrings(gr, ' ');
                int n = stoi(cubes.at(0));
                string color = cubes.at(1);
                int red = 0;
                int green = 0;
                int blue = 0;
                if (color == "red") red = n;
                if (color == "green") green = n;
                if (color == "blue") blue = n;
                if (red > redMax || green > greenMax || blue > blueMax) possible = false;
            }
        }
        if (possible) total += id;
    }
    cout << total << "\n";
}

void part2(vector<string>& input) {
    int total = 0;
    vector<string> games = getSubStrings(input, ':', "Game");
    for (const string& g: games) {
        int red = 0;
        int green = 0;
        int blue = 0;
        vector<string> game = getSubStrings(g, ';');

        for (const string& s: game) {
            vector<string> grab = getSubStrings(s, ',');
            for (const string& gr: grab) {
                vector<string> cubes = getSubStrings(gr, ' ');
                int n = stoi(cubes.at(0));
                string color = cubes.at(1);
                if (color == "red" && n > red) red = n;
                if (color == "green" && n > green) green = n;
                if (color == "blue" && n > blue) blue = n;
            }
        }
        total += red * green * blue;
    }
    cout << total << "\n";
}

int main() {
    string filename = "../Day_02/input02";
    int lineCount = getLineCount(filename);
    vector<string> input = getInput(filename, lineCount);
    int redMax = 12;
    int greenMax = 13;
    int blueMax = 14;

    auto t1 = Clock::now();
    part1(input, redMax, greenMax, blueMax); // 2551
    auto t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs" << "\n";

    t1 = Clock::now();
    part2(input); // 62811
    t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs" << "\n";
}
