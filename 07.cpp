#include <iostream>
#include <array>
#include <fmt/core.h>
#include <map>
#include "util.hpp"

using namespace std;
bool use_joker = false;

enum class Card {
    two = 0,
    three = 1,
    four = 2,
    five = 3,
    six = 4,
    seven = 5,
    eight = 6,
    nine = 7,
    t = 8,
    j = 9,
    q = 10,
    k = 11,
    a = 12
};

enum class Type {
    high = 0,
    pair = 1,
    twopair = 2,
    three = 3,
    fullhouse = 4,
    four = 5,
    five = 6
};

const map<Type, string> typenames = {
        {Type::high, "high card"},
        {Type::pair, "one pair"},
        {Type::twopair, "two pair"},
        {Type::three, "three of a kind"},
        {Type::fullhouse, "full house"},
        {Type::four, "four of a kind"},
        {Type::five, "five of a kind"},
};

typedef array<Card, 5> hand_ar;

constexpr string_view chars = "23456789TJQKA";

Type find_type(const hand_ar& ar) {
    array<int, 13> count{};
    for (const auto& c: ar) {
        ++count[static_cast<int>(c)];
    }
    if (use_joker) {
        int jokers = count[static_cast<int>(Card::j)];
        count[static_cast<int>(Card::j)] = 0;
        auto highest = ranges::max_element(count);
        count[highest - count.begin()] += jokers;
    }
    if (ranges::count(count, 5) == 1) {
        return Type::five;
    }
    if (ranges::count(count, 4) == 1) {
        return Type::four;
    }
    if (ranges::count(count, 3) == 1 && ranges::count(count, 2) == 1) {
        return Type::fullhouse;
    }
    if (ranges::count(count, 3) == 1) {
        return Type::three;
    }
    if (ranges::count(count, 2) == 2) {
        return Type::twopair;
    }
    if (ranges::count(count, 2) == 1) {
        return Type::pair;
    }
    return Type::high;
}

class Hand {
public:
    Hand() = delete;
    explicit Hand(const string& line) {
        for (size_t i = 0; i < 5; ++i) {
            _hand[i] = static_cast<Card>(chars.find_first_of(line[i]));
        }
        _bet = stoull(line.substr(5, line.length()));
        _type = find_type(_hand);
    }

    [[nodiscard]] const hand_ar& hand() const { return _hand; }
    [[nodiscard]] const size_t& bet() const { return _bet; }
    [[nodiscard]] Type type() const { return _type; }
    void setType(Type t) { this->_type = t; }

    bool operator==(const Hand& h) const {
        return this->_type == h._type &&
            this->_hand == h._hand;
    }

    bool operator!=(const Hand& h) const {
        return not(*this == h);
    }

    bool operator<(const Hand& h) const {
        if (this->_type < h._type) {
            return true;
        }
        if (this->_type > h._type) {
            return false;
        }
        for (size_t i = 0; i < 5; ++i) {
            if (this->_hand[i] != h._hand[i]) {
                if (use_joker) {
                    if (this->_hand[i] == Card::j) {
                        return true;
                    }
                    if (h._hand[i] == Card::j) {
                        return false;
                    }
                }
                return this->_hand[i] < h._hand[i];
            }
        }
        return false;
    }

    bool operator<=(const Hand& h) const {
        return (*this == h || *this < h);
    }

    bool operator>(const Hand& h) const {
        return h <= *this;
    }

    bool operator>=(const Hand& h) const {
        return h < *this;
    }


private:
    hand_ar _hand{};
    size_t _bet;
    Type _type;
};

ostream& operator<<(ostream& os, const Hand& h) {
    for (size_t i = 0; i < 5; ++i) {
        os << chars[static_cast<size_t>(h.hand()[i])];
    }
    os << fmt::format(" {}\t{}\n", h.bet(), typenames.at(h.type()));
    return os;
}

size_t solve(vector<Hand>& hands) {
    ranges::sort(hands);
    size_t ret = 0;
    for (size_t i = 1; const auto& h: hands) {
        ret += i++ * h.bet();
    }
    return ret;
}

int main() {
    linevec lines;
    get_input("../input/07.in", lines);
    vector<Hand> hands;
    for (const auto& line: lines) {
        hands.emplace_back(line);
    }
    cout << fmt::format("part 1: {}\n", solve(hands));
    use_joker = true;
    // find type again but with jokers
    for (auto& h: hands) {
        h.setType(find_type(h.hand()));
    }
    cout << fmt::format("part 2: {}\n", solve(hands));
}