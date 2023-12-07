#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "util.hpp"

using namespace std;

class Card {
public:
    Card() = delete;
    explicit Card(const std::string& line) {
        size_t pos1 = line.find_first_of(':');
        size_t pos2 = line.find_first_of('|');
        card_n = stoi(line.substr(line.find_first_of("0123456789"), pos1));
        stringstream win_ss(line.substr(pos1 + 1, pos2));
        stringstream my_ss(line.substr(pos2 + 1, line.length()));
        int n;
        while (win_ss >> n) {
            _win.push_back(n);
        }
        while (my_ss >> n) {
            _my.push_back(n);
        }
        ranges::sort(win());
        ranges::sort(my());
        vector<int> intersection;
        ranges::set_intersection(win(), my(), back_inserter(intersection));
        _wins = intersection.size();
    }

    [[nodiscard]] const size_t& n() const { return card_n; }
    vector<int>& win() { return _win; }
    vector<int>& my() { return _my; }
    [[nodiscard]] const size_t& wins() const { return _wins; }

private:
    size_t card_n;
    vector<int> _win;
    vector<int> _my;
    size_t _wins;
};

int part1(const vector<Card>& cards) {
    int ret = 0;
    // no ref to modify only local
    for (const auto& card: cards) {
        int value = 0;
        for (size_t i = 0; i < card.wins(); ++i) {
            if (value == 0) {
                ++value;
                continue;
            }
            value *= 2;
        }
        ret += value;
    }
    return ret;
}

int part2(const vector<Card>& cards) {
    int ret = 0;
    map<size_t, int> map;
    for (const auto& card: cards) {
        map[card.n()] += 1;
        for (size_t i = 0; i < card.wins(); ++i) {
            map[card.n() + i + 1] += map[card.n()];
        }
    }
    for (const auto& [key, val] : map) {
        ret += val;
    }
    return ret;
}

int main() {
    linevec lines;
    get_input("../input/04.in", lines);
    std::vector<Card> cards;
    for (const auto& line : lines) {
        cards.emplace_back(line);
    }
    cout << "part 1: " << part1(cards) << "\n";
    cout << "part 2: " << part2(cards) << "\n";
}