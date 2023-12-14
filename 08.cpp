#include <iostream>
#include <fmt/core.h>
#include <functional>
#include "util.hpp"

using namespace std;

class Node {
public:
    Node() = delete;
    explicit Node(const string& line) {
        _self = line.substr(0, 3);
        _left = line.substr(7, 3);
        _right = line.substr(12, 3);
    }
    [[nodiscard]] const string& self() const { return _self; }
    [[nodiscard]] const string& left() const { return _left; }
    [[nodiscard]] const string& right() const { return _right; }
private:
    string _self;
    string _left;
    string _right;
};

size_t part1(const string& instructions, const vector<Node>& nodes) {
    size_t ret = 0;
    auto current = nodes.begin();
    while (true) {
        for (const auto& c: instructions) {
            function<bool(Node)> pred;
            if (c == 'L') {
                pred = [current](const Node& n) { return current->left() == n.self(); };
            } else { // 'R'
                pred = [current](const Node& n) { return current->right() == n.self(); };
            }
            current = ranges::find_if(nodes, pred);
            ++ret;
            if (current->self() == "ZZZ") {
                return ret;
            }
        }
    }
}

size_t part2(const string& instructions, const vector<Node>& nodes) {
    vector<vector<Node>::const_iterator> start_nodes;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->self().ends_with('A')) {
            start_nodes.push_back(it);
        }
    }
    cout << start_nodes.size() << " starters\n";
    vector<size_t> pathlens;
    for (auto& current: start_nodes) {
        size_t ret = 0;
        bool looping = true;
        while (looping) {
            for (const auto& c: instructions) {
                if (not looping) {
                    break;
                }
                function<bool(Node)> pred;
                if (c == 'L') {
                    pred = [current](const Node& n) { return current->left() == n.self(); };
                } else { // 'R'
                    pred = [current](const Node& n) { return current->right() == n.self(); };
                }
                current = ranges::find_if(nodes, pred);
                ++ret;
                if (current->self().ends_with('Z')) {
                    cout << "found one at " << current->self() << "\n";
                    pathlens.push_back(ret);
                    looping = false;
                    break;
                }
            }
        }
    }
    cout << "lens\n";
    for (const auto& l: pathlens) {
        cout << l << "\n";
    }
    // didn't want to write code for least common multiplier so found lcm on
    // https://www.calculatorsoup.com/calculators/math/lcm.php
    return 0;
}

int main() {
    linevec lines;
//    get_input("../input/ex.in", lines);
    get_input("../input/08.in", lines);
    vector<Node> nodes;
    for (size_t i = 2; i < lines.size(); ++i) {
        nodes.emplace_back(lines[i]);
    }
    cout << fmt::format("part 1: {}\n", part1(lines[0], nodes));
    cout << fmt::format("part 2: {}\n", part2(lines[0], nodes));
}