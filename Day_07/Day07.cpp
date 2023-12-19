#include "../helper.hpp"

using std::sort;

vector CARDS_1 = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
vector CARDS_2 = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

enum TYPE {
    HIGH_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_OF_A_KIND = 3,
    FULL_HOUSE = 23,
    FOUR_OF_A_KIND = 44,
    FIVE_OF_A_KIND = 55
};

class Hand {
public:
    Hand(const int type_, const int bid_, const vector<int>& cards_, const string& hand_)
        : type(type_),
          bid(bid_),
          rank(0),
          cards(cards_),
          hand(hand_) {
    }

    Hand(const int type_, const int bid_, const vector<int>& cards_, const int rank_, const vector<int>& count_,
         const string& hand_)
        : type(type_),
          bid(bid_),
          rank(rank_),
          cards(cards_),
          count(count_),
          hand(hand_) {
    }

    bool operator<(const Hand& other) const {
        if (type == other.type) {
            for (int i = 0; i < 5; ++i) {
                if (cards[i] != other.cards[i])
                    return cards[i] < other.cards[i];
            }
            return false;
        }
        return type < other.type;
    }

    int type;
    int bid;
    int rank;
    vector<int> cards;
    vector<int> count;
    string hand;
};

inline std::ostream& operator<<(std::ostream& stream, const Hand& hand) {
    stream << hand.hand << "\t";
    switch (hand.type) {
        case FIVE_OF_A_KIND: stream << "Five of a Kind\t";
            break;
        case FOUR_OF_A_KIND: stream << "Four of a Kind\t";
            break;
        case FULL_HOUSE: stream << "Full House\t\t";
            break;
        case THREE_OF_A_KIND: stream << "Three of a Kind\t";
            break;
        case TWO_PAIR: stream << "Two Pair\t\t";
            break;
        case ONE_PAIR: stream << "One Pair\t\t";
            break;
        default: stream << "High Card\t\t";
    }
    stream << "\t";
    for (const auto card: hand.cards) {
        stream << card << "\t";
    }
    stream << "\t$" << hand.bid << "  \t#" << hand.rank;
    return stream;
}

void setRanks(vector<Hand>& hands) {
    int rank = 0;
    for (Hand& h: hands) {
        h.rank = ++rank;
    }
}

vector<int> convertHand(const string& hand) {
    vector<int> hand_c(hand.length());
    for (size_t i = 0; i < hand.length(); ++i) {
        if (hand[i] == 'A') hand_c[i] = 14;
        else if (hand[i] == 'K') hand_c[i] = 13;
        else if (hand[i] == 'Q') hand_c[i] = 12;
        else if (hand[i] == 'J') hand_c[i] = 11;
        else if (hand[i] == 'T') hand_c[i] = 10;
        else hand_c[i] = hand[i] - '0';
    }
    return hand_c;
}

vector<int> countCards(const string& hand) {
    vector<int> count(CARDS_1.size());
    for (const char c: hand) {
        for (size_t i = 0; i < CARDS_1.size(); ++i) {
            if (c == CARDS_1[i]) count[i]++;
        }
    }
    return count;
}

int identifyHand(const string& hand) {
    auto count_sorted = countCards(hand);
    std::ranges::sort(count_sorted);

    const vector five_of_a_kind = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5};
    if (count_sorted == five_of_a_kind) return FIVE_OF_A_KIND;

    const vector four_of_a_kind = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4};
    if (count_sorted == four_of_a_kind) return FOUR_OF_A_KIND;

    const vector full_house = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3};
    if (count_sorted == full_house) return FULL_HOUSE;

    const vector three_of_a_kind = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3};
    if (count_sorted == three_of_a_kind) return THREE_OF_A_KIND;

    const vector two_pair = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2};
    if (count_sorted == two_pair) return TWO_PAIR;

    const vector one_pair = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2};
    if (count_sorted == one_pair) return ONE_PAIR;

    return HIGH_CARD;
}

vector<int> convertHand2(const string& hand) {
    vector<int> hand_c(hand.length());
    for (size_t i = 0; i < hand.length(); ++i) {
        if (hand[i] == 'A') hand_c[i] = 14;
        else if (hand[i] == 'K') hand_c[i] = 13;
        else if (hand[i] == 'Q') hand_c[i] = 12;
        else if (hand[i] == 'J') hand_c[i] = 1;
        else if (hand[i] == 'T') hand_c[i] = 10;
        else hand_c[i] = hand[i] - '0';
    }
    return hand_c;
}

vector<int> countCards2(const string& hand) {
    vector<int> count(CARDS_2.size());
    for (const char c: hand) {
        for (size_t i = 0; i < CARDS_2.size(); ++i) {
            if (c == CARDS_2[i]) count[i]++;
        }
    }
    return count;
}

int identifyHand2(const vector<int>& count) {
    auto count_sorted = count;
    std::ranges::sort(count_sorted);

    const vector five_of_a_kind = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5};
    if (count_sorted == five_of_a_kind) return FIVE_OF_A_KIND;

    const vector four_of_a_kind = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4};
    if (count_sorted == four_of_a_kind) return FOUR_OF_A_KIND;

    const vector full_house = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3};
    if (count_sorted == full_house) return FULL_HOUSE;

    const vector three_of_a_kind = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3};
    if (count_sorted == three_of_a_kind) return THREE_OF_A_KIND;

    const vector two_pair = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2};
    if (count_sorted == two_pair) return TWO_PAIR;

    const vector one_pair = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2};
    if (count_sorted == one_pair) return ONE_PAIR;

    return HIGH_CARD;
}

vector<vector<int>> getCountsWithJokersReplaced(const vector<int>& count) {
    vector<vector<int>> p;

    // count with no jokers shouldn't really get passed into the function
    // one joker
    if (count[12] == 1) {
        for (int i = 0; i < 12; ++i) {
            auto c = count;
            c[12]--;
            c[i]++;
            p.push_back(c);
        }
        return p;
    }

    // two jokers
    if (count[12] == 2) {
        for (int i = 0; i < 12; ++i) {
            auto c = count;
            c[12]--;
            c[i]++;
            for (int j = i; j < 12; ++j) {
                c[12]--;
                c[j]++;
                p.push_back(c);
            }
        }
        return p;
    }

    // three jokers
    if (count[12] == 3) {
        for (int i = 0; i < 12; ++i) {
            auto c = count;
            c[12]--;
            c[i]++;
            for (int j = i; j < 12; ++j) {
                c[12]--;
                c[j]++;
                for (int k = j; k < 12; ++k) {
                    c[12]--;
                    c[k]++;
                    p.push_back(c);
                }
            }
        }
        return p;
    }

    // four jokers
    if (count[12] == 4) {
        for (int i = 0; i < 12; ++i) {
            auto c = count;
            c[12]--;
            c[i]++;
            for (int j = i; j < 12; ++j) {
                c[12]--;
                c[j]++;
                for (int k = j; k < 12; ++k) {
                    c[12]--;
                    c[k]++;
                    for (int l = k; l < 12; ++l) {
                        c[12]--;
                        c[l]++;
                        p.push_back(c);
                    }
                }
            }
        }
        return p;
    }

    return {count}; // shouldn't be reached
}

int getBestTypeWithJokersReplaced(const vector<int>& count) {
    int type = identifyHand2(count);

    if (type == FIVE_OF_A_KIND)
        return FIVE_OF_A_KIND;

    const auto countsJokersReplaced = getCountsWithJokersReplaced(count);
    for (auto c: countsJokersReplaced) {
        type = std::max(type, identifyHand2(c));
    }

    return type;
}

int part2(const vector<string>& input) {
    vector<Hand> hands;
    for (const string& s: input) {
        auto line = getSubStrings(s, ' ');
        string hand_sorted(line[0]);
        std::ranges::sort(hand_sorted);
        auto count = countCards2(hand_sorted);
        Hand hand{
            identifyHand2(count),
            stoi(line[1]),
            convertHand2(line[0]),
            count[12] > 0 ? count[12] : 0, // setting rank to #jokers
            count,
            line[0]
        };
        hands.push_back(hand);
    }

    for (Hand& h: hands) {
        if (h.rank > 0) h.type = getBestTypeWithJokersReplaced(h.count); // hand contains joker(s)
    }

    sort(hands.begin(), hands.end());
    setRanks(hands);
    int total = 0;
    for (const Hand& hand: hands) {
        // cout << hand << "\n";
        total += hand.bid * hand.rank;
    }

    return total;
}

int part1(const vector<string>& input) {
    vector<Hand> hands;
    for (const string& s: input) {
        auto line = getSubStrings(s, ' ');
        string hand_sorted(line[0]);
        std::ranges::sort(hand_sorted);
        Hand hand{
            identifyHand(hand_sorted),
            stoi(line[1]),
            convertHand(line[0]),
            line[0]
        };
        hands.push_back(hand);
    }

    sort(hands.begin(), hands.end());
    setRanks(hands);
    int total = 0;
    for (const Hand& hand: hands) {
        // cout << hand << "\n";
        total += hand.bid * hand.rank;
    }
    return total;
}

int main() {
    auto constexpr TEST = 0;
    auto constexpr TEST_FILE = "../test", INPUT_FILE = "../Day_07/input07";
    auto const filename = TEST == 1 ? TEST_FILE : INPUT_FILE;
    auto const line_count = getLineCount(filename);
    auto const input = getInput(filename, line_count);

    auto t1 = Clock::now();
    cout << part1(input); // 253603890
    auto t2 = Clock::now();
    cout << " (" << MICRO_S(t2 - t1).count() << " μs)\n";

    t1 = Clock::now();
    cout << part2(input);
    t2 = Clock::now(); // 253630098
    cout << " (" << MILLI_S(t2 - t1).count() << " ms)\n";
}
