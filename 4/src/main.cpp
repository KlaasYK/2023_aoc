// Copyright 2023 Klaas Kliffen
// SPDX-License-Identifier: Apache-2.0

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <numeric>
#include <regex>
#include <set>

#include "util.hpp"

std::regex const LINE("Card\\s+(\\d+):([\\d\\s]+)\\|([\\d\\s]+)");
std::regex const NUMBER("\\d+");

std::vector<unsigned> parse_numbers(std::string const &line)
{
    std::set<unsigned> numbers;
    auto start = std::sregex_iterator(line.begin(), line.end(), NUMBER);
    auto end = std::sregex_iterator();
    for (auto it = start; it != end; ++it)
        numbers.insert(std::stoul((*it).str()));

    return std::vector(numbers.begin(), numbers.end());
}

unsigned parse_line(std::string const &line)
{
    std::smatch m;
    if (std::regex_match(line, m, LINE))
    {
        auto const winning = parse_numbers(m[2]);
        auto const numbers = parse_numbers(m[3]);
        std::vector<unsigned> common;
        std::set_intersection(winning.begin(), winning.end(), numbers.begin(), numbers.end(), std::back_inserter(common));
        std::cout << m[1] << ' ' << common.size() << '\n';
        return common.size() > 0 ? 1 << (common.size() - 1) : 0;
    } else {
        std::cout << line << '\n';
    }

    return 0;
}

int main(int argc, char *argv[])
try
{
    typedef std::istream_iterator<util::Line> LineIt;

    // Read input file
    std::ifstream in(util::open_input_stream(argc, argv));
    std::vector<std::string> lines((LineIt(in)), LineIt());

    std::vector<unsigned> cards;
    std::transform(lines.begin(), lines.end(),
                   std::back_inserter(cards),
                   parse_line);

    unsigned sum = std::accumulate(cards.begin(), cards.end(), 0);

    // 9984 too low

    std::cout << "sum: " << sum << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
