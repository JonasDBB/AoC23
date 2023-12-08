#include <vector>
#include <sstream>
#include <iostream>
#include <fmt/core.h>
#include "util.hpp"

using namespace std;

class Range {
public:
    Range() = delete;
    Range(ssize_t dst, ssize_t src, ssize_t l) : dst_start(dst), src_start(src), len(l) {}
    const ssize_t dst_start;
    const ssize_t src_start;
    const ssize_t len;
    [[nodiscard]] optional<ssize_t> dst_mapping(ssize_t src) const {
        if (src >= src_start && src < src_start + len) {
            return src - (src_start - dst_start);
        }
        return nullopt;
    }
};

vector<ssize_t> get_seeds(const string& line) {
    vector<ssize_t> seeds;
    stringstream ss(line);
    string str;
    ssize_t n;
    ss >> str;
    while (ss >> n) {
        seeds.push_back(n);
    }
    return seeds;
}

vector<vector<Range>> get_mappings(const linevec& lines) {
    vector<vector<Range>> mapping;
    for (const auto& line: lines) {
        if (line.empty()) {
            mapping.emplace_back();
            continue;
        }
        // mapping names
        if (isalpha(line.front())) {
            continue;
        }
        if (not isnumber(line.front())) {
            cerr << "SHOULD NEVER HAPPEN\n";
            abort();
        }
        stringstream rss(line);
        ssize_t dst, src, l;
        rss >> dst >> src >> l;
        mapping.back().emplace_back(dst, src, l);
    }
    return mapping;
}

ssize_t part1(const vector<ssize_t>& seeds, const vector<vector<Range>>& mappings) {
    ssize_t min_end_loc = -1;
    for (const auto& seed: seeds) {
        ssize_t val = seed;
        for (const auto& map: mappings) {
            optional<ssize_t> range_val;
            for (const auto& range: map) {
                range_val = range.dst_mapping(val);
                if (range_val.has_value()) {
                    break;
                }
            }
            val = range_val.value_or(val);
        }
        min_end_loc = min_end_loc == -1 ? val : min(min_end_loc, val);
    }
    return min_end_loc;
}

// takes like 3 min to run on my macbook m1 pro 🥲
ssize_t part2(const vector<ssize_t>& seeds, const vector<vector<Range>>& mappings) {
    ssize_t min_end_loc = -1;
    for (auto it = seeds.begin(); it < seeds.end(); it += 2) {
        for (ssize_t seed = 0; seed < *(it + 1); ++seed) {
            ssize_t val = *it + seed;
            for (const auto& map: mappings) {
                optional<ssize_t> range_val;
                for (const auto& range: map) {
                    range_val = range.dst_mapping(val);
                    if (range_val.has_value()) {
                        break;
                    }
                }
                val = range_val.value_or(val);
            }
            min_end_loc = min_end_loc == -1 ? val : min(min_end_loc, val);
        }
    }
    return min_end_loc;
}

int main() {
    linevec lines;
    get_input("../input/05.in", lines);
    vector<ssize_t> seeds = get_seeds(lines[0]);
    vector<vector<Range>> mapping = get_mappings(lines);
    cout << fmt::format("part 1: {}\n", part1(seeds, mapping));
    cout << fmt::format("part 2: {}\n", part2(seeds, mapping));
}