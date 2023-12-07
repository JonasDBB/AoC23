#include <iostream>
#include <vector>
#include <cmath>
#include "util.hpp"

typedef std::vector<char> row;
typedef std::vector<row> matrix;

std::ostream& operator<<(std::ostream& os, const matrix& m) {
    for (const auto& r : m) {
        for (const auto& c : r) {
            os << c;
        }
        os << "\n";
    }
    return os;
}

void gen_matrix(matrix& dest) {
    linevec lines;
    get_input("../input/03.in", lines);
    for (const auto& line : lines) {
        row r;
        for (const auto& c : line) {
            r.push_back(c);
        }
        dest.push_back(r);
    }
}

bool isdigit(const char& c) {
    return c >= '0' && c <= '9';
}

bool issymbol(const char& c) {
    return !isdigit(c) && c != '.';
}

int nr_value(const row& rw, size_t x) {
    int ret = 0;
    while (x != 0 && isdigit(rw[x - 1])) {
        --x;
    }
    while (x < rw.size() && isdigit(rw[x])) {
        ret *= 10;
        ret += rw[x++] - '0';
    }
    return ret;
}

bool has_adjacent_symbol(const matrix& m, size_t y, size_t x) {
    if (y > 0) {
        // top left
        if (x > 0) {
            if (issymbol(m[y - 1][x - 1])) { return true; }
        }
        // top
        if (issymbol(m[y - 1][x])) { return true; }
        // top right
        if (x < m[y].size() - 1) {
            if (issymbol(m[y - 1][x + 1])) { return true; }
        }
    }
    // left
    if (x > 0) {
        if (issymbol(m[y][x - 1])) { return true; }
    }
    // right
    if (x < m[y].size() - 1) {
        if (issymbol(m[y][x + 1])) { return true; }
    }
    if (y < m.size() - 1) {
        // bottom left
        if (x > 0) {
            if (issymbol(m[y + 1][x - 1])) { return true; }
        }
        // bottom
        if (issymbol(m[y + 1][x])) { return true; }
        // bottom right
        if (x < m[y].size() - 1) {
            if (issymbol(m[y + 1][x + 1])) { return true; }
        }
    }

    return false;
}

std::optional<int> part_value(const matrix& m, size_t y, size_t x) {
    bool is_part = false;

    auto tmp_x = x;
    while (tmp_x < m[y].size() && isdigit(m[y][tmp_x])) {
        if (has_adjacent_symbol(m, static_cast<ssize_t>(y), static_cast<ssize_t>(tmp_x++))) {
            is_part = true;
            break;
        }
    }
    if (is_part) {
        return nr_value(m[y], x);
    }
    return std::nullopt;
}

int part1(const matrix& m) {
    int sum = 0;
    for (size_t y = 0; y < m.size(); ++y) {
        for (size_t x = 0; x < m[y].size(); ++x) {
            if (isdigit(m[y][x])) {
                auto part_val = part_value(m, y, x);
                if (part_val.has_value()) {
                    sum += part_val.value();
                }
                while (x < m[y].size() && isdigit(m[y][x])) { ++x; }
            }
        }
    }
    return sum;
}

std::optional<int> get_gear_val(const matrix& m, size_t y, size_t x) {
    int n1 = 0;
    int n2 = 0;
    // top left
    if (x != 0 && y != 0 && isdigit(m[y - 1][x - 1])) {
        n1 = nr_value(m[y - 1], x - 1);
    }
    // top, skip if top left is also digit
    if (y != 0 && isdigit(m[y - 1][x]) && not isdigit(m[y - 1][x - 1])) {
        n1 = nr_value(m[y - 1], x);
    }
    // top right, skip if top is also digit
    if (y != 0 && x < m[y].size() - 1 && isdigit(m[y - 1][x + 1]) && not isdigit(m[y - 1][x])) {
        if (n1 != 0) {
            n2 = nr_value(m[y - 1], x + 1);
        } else {
            n1 = nr_value(m[y - 1], x + 1);
        }
    }
    // left
    if (x != 0 && isdigit(m[y][x - 1])) {
        if (n1 != 0 && n2 != 0) {
            return std::nullopt;
        } else if (n1 != 0) {
            n2 = nr_value(m[y], x - 1);
        } else {
            n1 = nr_value(m[y], x - 1);
        }
    }
    // right
    if (x < m[y].size() - 1 && isdigit(m[y][x + 1])) {
        if (n1 != 0 && n2 != 0) {
            return std::nullopt;
        } else if (n1 != 0) {
            n2 = nr_value(m[y], x + 1);
        } else {
            n1 = nr_value(m[y], x + 1);
        }
    }
    // bottom left
    if (x != 0 && y < m.size() - 1 && isdigit(m[y + 1][x - 1])) {
        if (n1 != 0 && n2 != 0) {
            return std::nullopt;
        } else if (n1 != 0) {
            n2 = nr_value(m[y + 1], x - 1);
        } else {
            n1 = nr_value(m[y + 1], x - 1);
        }
    }
    // bottom, skip if bottom left is also digit
    if (y < m.size() - 1 && isdigit(m[y + 1][x]) && not isdigit(m[y + 1][x - 1])) {
        if (n1 != 0 && n2 != 0) {
            return std::nullopt;
        } else if (n1 != 0) {
            n2 = nr_value(m[y + 1], x);
        } else {
            n1 = nr_value(m[y + 1], x);
        }
    }
    // bottom right, skip if bottom is also digit
    if (y < m.size() - 1 && x < m[y].size() - 1 && isdigit(m[y + 1][x + 1]) && not isdigit(m[y + 1][x])) {
        if (n1 != 0 && n2 != 0) {
            return std::nullopt;
        } else if (n1 != 0) {
            n2 = nr_value(m[y + 1], x + 1);
        } else {
            n1 = nr_value(m[y + 1], x + 1);
        }
    }

    if (n2 == 0) {
        return std::nullopt;
    }
    return n1 * n2;
}

int part2(const matrix& m) {
    int sum = 0;
    for (size_t y = 0; y < m.size(); ++y) {
        for (size_t x = 0; x < m[y].size(); ++x) {
            if (m[y][x] == '*') {
                sum += get_gear_val(m, y, x).value_or(0);
            }
        }
    }
    return sum;
}

int main() {
    matrix input;
    gen_matrix(input);
    std::cout << "part 1: " << part1(input) << "\n";
    std::cout << "part 2: " << part2(input) << "\n";
    return 0;
}
