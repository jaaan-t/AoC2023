#include "../helper.hpp"

using std::min;
using std::max;
using std::stol;

vector<vector<long>> getMap(const vector<string>& input, const string& map_name) {
    vector<vector<long>> map;

    // find start and end of map
    long map_start = 0, map_end = 0;
    for (long i = 0; i < input.size(); ++i) {
        if (input[i] == map_name) {
            map_start = i + 1;
        }
    }
    for (long i = map_start; i < input.size(); ++i) {
        if (input[i].empty()) {
            map_end = i;
            break;
        }
    }

    // get map details
    for (long i = map_start; i < map_end; ++i) {
        vector<string> range = getSubStrings(input[i], ' ');
        auto const dest = stol(range[0]);
        auto const source = stol(range[1]);
        auto const len = stol(range[2]);
        map.push_back(vector{source, dest, len});
    }

    return map;
}

vector<vector<long>> getMapInfo(const vector<vector<long>>& map, const string& name) {
    vector<vector<long>> mapInfo;

    long source_start = LONG_MAX;
    long source_end = LONG_MIN;
    long dest_start = LONG_MAX;
    long dest_end = LONG_MIN;

    for (const auto& entry: map) {
        auto const source = entry[0];
        auto const dest = entry[1];
        auto const len = entry[2];
        source_start = min(source_start, source);
        source_end = max(source_end, source + len - 1);
        dest_start = min(dest_start, dest);
        dest_end = max(dest_end, dest + len - 1);
    }
    cout << name << ":  \t";
    cout << source_start << ", " << source_end << "~\n";

    return mapInfo;
}

long lookup(const vector<vector<long>>& map, long const n) {
    for (const auto& entry: map) {
        auto const source = entry[0];
        auto const dest = entry[1];
        auto const len = entry[2];
        if (n >= source && n < source + len) {
            return n + dest - source;
        }
    }
    return n;
}

bool withinRange(long const n, long const start, long const range) {
    return n >= start && n < start + range;
}

bool overlap(long const start1, long const range1, long const start2, long const range2) {
    return withinRange(start1, start2, range2)
           || withinRange(start1 + range1 - 1, start2, range2)
           || withinRange(start2, start1, range1)
           || withinRange(start2 + range2 - 1, start1, range1);
}

void lookup2(const vector<vector<long>>& map, vector<long>& seeds) {
    for (long& seed: seeds) {
        for (const auto& entry: map) {
            auto const source = entry[0];
            auto const dest = entry[1];
            auto const len = entry[2];
            if (seed >= source && seed < source + len) {
                seed += dest - source;
                break;
            }
        }
    }
}

long part2(const vector<string>& input, const vector<string>& mapNames) {
    // get maps
    vector<vector<vector<long>>> maps(mapNames.size());
    for (int i = 0; i < mapNames.size(); ++i) {
        maps[i] = getMap(input, mapNames[i]);
    }

    /* get map info
    for (int i = 0; i < maps.size(); ++i) {
        getMapInfo(maps[i], mapNames[i]);
    }
    */

    // get seed ranges
    auto const substr = getSubStrings(input[0], ' ');
    vector<long> seedRanges(substr.size() - 1);
    for (long i = 1; i < substr.size(); ++i) {
        seedRanges[i - 1] = stol(substr[i]);
    }

    /* check for overlap between ranges
    for (int i = 0; i < seedRanges.size(); i += 2) {
        auto const start1 = seedRanges[i];
        auto const range1 = seedRanges[i + 1];
        cout << start1 << "," << range1 << "\n";
        for (int j = 0; j < seedRanges.size(); j += 2) {
            auto const start2 = seedRanges[j];
            auto const range2 = seedRanges[j + 1];
            if (overlap(start1, range1, start2, range2) && start1 != start2) {
                cout << start1 << "," << start2 << "\n";
            }
        }
    }
    */

    // min and max seeds
    vector<long> seedsMinMax;
    long numSeeds = 0;
    for (int i = 0; i < seedRanges.size(); i += 2) {
        numSeeds += seedRanges[i + 1];
        seedsMinMax.push_back(seedRanges[i]);
        seedsMinMax.push_back(seedRanges[i] + seedRanges[i + 1] - 1);
    }

    // all seeds
    vector<long> seeds(numSeeds);
    long numSeeds2 = 0;
    for (int i = 0; i < seedRanges.size(); i += 2) {
        long const start = seedRanges[i];
        long const range = seedRanges[i + 1];
        for (long j = start; j < start + range; ++j) {
            seeds[numSeeds2] = j;
            ++numSeeds2;
        };
    }

    for (const auto& map: maps) {
        lookup2(map, seeds);
    }

    long lowest = LONG_MAX;
    for (long s: seeds) {
        lowest = min(lowest, s);
    }

    return lowest;
}

long part1(const vector<string>& input, const vector<string>& mapNames) {
    // get maps
    vector<vector<vector<long>>> maps(mapNames.size());
    for (int i = 0; i < mapNames.size(); ++i) {
        maps[i] = getMap(input, mapNames[i]);
    }

    // get seeds
    auto const substr = getSubStrings(input[0], ' ');
    vector<long> seeds(substr.size() - 1);
    for (long i = 1; i < substr.size(); ++i) {
        seeds[i - 1] = stol(substr[i]);
    }

    // lookup seeds
    long lowest = LONG_MAX;
    for (long const seed: seeds) {
        long n = seed;
        for (const auto& map: maps) {
            n = lookup(map, n);
        }
        lowest = min(lowest, n);
    }

    return lowest;
}

int main() {
    auto constexpr TEST = 0;
    auto constexpr TEST_FILE = "../test", INPUT_FILE = "input05";
    auto const filename = TEST == 1 ? TEST_FILE : INPUT_FILE;
    auto const lineCount = getLineCount(filename);
    auto const input = getInput(filename, lineCount + 1); // extra line so convertToMap will work

    const vector<string> mapNames = {
        "seed-to-soil map:",
        "soil-to-fertilizer map:",
        "fertilizer-to-water map:",
        "water-to-light map:",
        "light-to-temperature map:",
        "temperature-to-humidity map:",
        "humidity-to-location map:"
    };

    auto t1 = Clock::now();
    cout << part1(input, mapNames); // 177942185
    auto t2 = Clock::now();
    cout << " (" << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs)\n";

    t1 = Clock::now();
    cout << part2(input, mapNames); // 69841803 (~ 3 m)
    t2 = Clock::now();
    cout << " (" << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << " s)\n";
}
