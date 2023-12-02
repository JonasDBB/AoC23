#include <iostream>
#include <sstream>
#include "util.hpp"

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

// wow so ugly :')
int part1(const linevec& lines) {
    int sum = 0;
    for (const auto& line : lines) {
        bool valid_game = true;
        std::stringstream ss(line);
        std::string str;
        int game_nr;
        int cube_count;
        // skip "Game"
        ss >> str;
        ss >> game_nr;
        // skip ":"
        ss >> str;
        while (ss.good() && valid_game) {
            ss >> cube_count;
            ss >> str;
            if (str.rfind("red", 0) == 0) {
                if (cube_count > MAX_RED) {
                    valid_game = false;
                }
            } else if (str.rfind("green", 0) == 0) {
                if (cube_count > MAX_GREEN) {
                    valid_game = false;
                }
            } else if (str.rfind("blue", 0) == 0) {
                if (cube_count > MAX_BLUE) {
                    valid_game = false;
                }
            } else {
                std::cerr << "SHOULD NEVER HAPPEN" << std::endl;
                abort();
            }
        }
        if (valid_game) {
            sum += game_nr;
        }
    }
    return sum;
}

int get_power(const std::string& line) {
    int min_red = 0;
    int min_green = 0;
    int min_blue = 0;
    size_t pos = line.find_first_of(':') + 1;
    while (true) {
        size_t end = line.find_first_of(';', pos);
        end = end == std::string::npos ? line.length() : end;
        std::string hand = line.substr(pos, end - pos);

        std::stringstream ss(hand);
        int n;
        std::string str;
        while (ss.good()) {
            ss >> n;
            ss >> str;
            if (str.rfind("red", 0) == 0) {
                min_red = n > min_red ? n : min_red;
            } else if (str.rfind("green", 0) == 0) {
                min_green = n > min_green ? n : min_green;
            } else if (str.rfind("blue", 0) == 0) {
                min_blue = n > min_blue ? n : min_blue;
            } else {
                std::cerr << "SHOULD NEVER HAPPEN" << std::endl;
                abort();
            }
        }

        pos = end + 1;
        if (end == line.length()) {
            break;
        }
    }
    return min_red * min_green * min_blue;
}

int part2(const linevec& lines) {
    int sum = 0;
    for (const auto& line : lines) {
        sum += get_power(line);
    }
    return sum;
}

int main() {
    linevec lines;
    get_input("../input/02.in", lines);
    std::cout << "part 1: " << part1(lines) << "\n";
    std::cout << "part 2: " << part2(lines) << "\n";
    return 0;
}