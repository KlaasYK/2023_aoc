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
#include <queue>

#include "util.hpp"

std::regex const NUMBER("\\d+");

std::vector<unsigned long> parse_numbers(std::string const &line)
{
    std::vector<unsigned long> numbers;
    auto start = std::sregex_iterator(line.begin(), line.end(), NUMBER);
    auto end = std::sregex_iterator();
    std::transform(start, end, std::back_inserter(numbers), [](auto val)
                   { return std::stoul(val.str()); });

    return numbers;
}

unsigned long wins(unsigned long time, unsigned long distance)
{
    unsigned w = 0;
    for (unsigned long t = 0; t != time; ++t)
        if ((time - t) * t > distance)
            ++w;
    return w;
}

int main(int argc, char *argv[])
try
{
    typedef std::istream_iterator<util::Line> LineIt;

    std::ifstream in(util::open_input_stream(argc, argv));
    std::vector<std::string> lines((LineIt(in)), LineIt());

    auto const times = parse_numbers(lines[0]);
    auto const distances = parse_numbers(lines[1]);

    // Part 1
    unsigned long total = 1;
    for (unsigned i = 0; i != times.size(); ++i)
        total *= wins(times[i], distances[i]);

    std::cout << "Part 1: " << total << '\n';

    std::erase(lines[0], ' ');
    std::erase(lines[1], ' ');
    auto const times2 = parse_numbers(lines[0]);
    auto const distances2 = parse_numbers(lines[1]);

    std::cout << "Part 2: " << wins(times2[0], distances2[0]) << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
