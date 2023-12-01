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

#include "util.hpp"

char find_first_digit(std::string const &line)
{
    for (auto c : line)
        if (std::isdigit(c))
            return c - '0';

    throw std::runtime_error("No digit found");
}

unsigned parse_line(std::string const &line)
{
    // find first digit
    auto first = find_first_digit(line);

    // find second digit (reversed)
    std::string reversed(line.rbegin(), line.rend());
    auto last = find_first_digit(reversed);

    return first * 10 + last;
}

int main(int argc, char *argv[])
try
{
    typedef std::istream_iterator<util::Line> LineIt;

    // Read input file
    std::ifstream in(util::open_input_stream(argc, argv));
    std::vector<std::string> lines((LineIt(in)), LineIt());

    std::vector<unsigned> values;
    std::transform(lines.begin(), lines.end(),
                   std::back_inserter(values),
                   parse_line);

    // Part 1
    unsigned total = std::accumulate(values.begin(), values.end(), 0);
    std::cout << "Calibration value: " << total << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
