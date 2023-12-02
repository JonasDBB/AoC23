#include <iostream>
#include "util.hpp"

int part1(const linevec& lines) {
    int sum = 0;
    for (const auto& line : lines) {
        sum += (line[line.find_first_of("0123456789")] - '0') * 10;
        sum += line[line.find_last_of("0123456789")] - '0';

    }
    return sum;
}

constexpr std::array<std::string_view, 10> digit_words = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int find_first(const std::string& line) {
    size_t pos = line.find_first_of("0123456789");
    int ret = pos == std::string::npos ? 0 : line[pos] - '0';
    int digit_val = 0;
    for (const auto& nr_word : digit_words) {
        size_t word_pos = line.find(nr_word);
        if (word_pos != std::string::npos && word_pos < pos) {
            pos = word_pos;
            ret = digit_val;
        }
        ++digit_val;
    }
    return ret;
}

int find_last(const std::string& line) {
    size_t pos = line.find_last_of("0123456789");
    int ret = pos == std::string::npos ? 0 : line[pos] - '0';
    pos = pos == std::string::npos ? 0 : pos;
    int digit_val = 0;
    for (const auto& nr_word : digit_words) {
        size_t word_pos = line.rfind(nr_word);
        if (word_pos != std::string::npos && word_pos > pos) {
            pos = word_pos;
            ret = digit_val;
        }
        ++digit_val;
    }
    return ret;
}

int part2(const linevec& lines) {
    int sum = 0;
    for (const auto& line : lines) {
        sum += find_first(line) * 10;
        sum += find_last(line);
    }
    return sum;
}

int main() {
    linevec lines;
    get_input("../input/01.in", lines);
    std::cout << "part 1: " << part1(lines) << "\n";
    std::cout << "part 2: " << part2(lines) << "\n";
    return 0;
}
