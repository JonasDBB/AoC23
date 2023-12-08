#include <iostream>
#include <fmt/core.h>
#include <sstream>
#include "util.hpp"

using namespace std;

vector<int> getnums(const string& line) {
    stringstream ss(line);
    string str;
    int n;
    ss >> str;
    vector<int> ret;
    while (ss >> n) {
        ret.push_back(n);
    }
    return ret;
}

size_t get_num_from_line(const string& line) {
    string time = line.substr(10, line.size());
    auto [beg, end] = ranges::remove(time, ' ');
    time.erase(beg, end);
    size_t t = stoull(time);
    return t;
}

int part1(const vector<int>& times, const vector<int>& dists) {
    int ret = 0;
    for (size_t i = 0; i < times.size(); ++i) {
        int possibilities = 0;
        for (int t = 1; t < times[i]; ++t) {
            int velocity = t;
            int time_left = times[i] - t;
            if (velocity * time_left > dists[i]) {
                ++possibilities;
            // after dists start going down again
            } else if (possibilities != 0) {
                break;
            }
        }
        ret = ret == 0 ? possibilities : ret * possibilities;
    }
    return ret;
}

size_t part2(size_t time, size_t dist) {
    size_t low = 0;
    for (size_t i = 1; i < time; ++i) {
        if (i * (time - i) > dist) {
            low = i;
            break;
        }
    }
    size_t high = 0;
    for (size_t i = time; i > 0; --i) {
        if (i * (time - i) > dist) {
            high = i;
            break;
        }
    }
    return high - low + 1;
}

int main() {
    linevec lines;
    get_input("../input/06.in", lines);
    vector<int> times = getnums(lines[0]);
    vector<int> dists = getnums(lines[1]);
    if (times.size() != dists.size()) {
        abort();
    }
    cout << fmt::format("part 1: {}\n", part1(times, dists));
    size_t time = get_num_from_line(lines[0]);
    size_t dist = get_num_from_line(lines[1]);
    cout << fmt::format("part 2: {}\n", part2(time, dist));
}