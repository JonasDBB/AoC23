#include <vector>
#include <fstream>
#include "util.hpp"

void get_input(const std::string& infile, linevec& lines) {
    std::ifstream input(infile);
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }
}