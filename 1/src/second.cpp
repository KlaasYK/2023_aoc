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

// Use "X" to align so that idx % 10 equals the value
std::vector<std::string> const TEXT_DIGITS({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"});

unsigned find_first_digit(std::string const &line)
{
    unsigned minIdx = std::numeric_limits<unsigned>::max();
    unsigned minDigit = 0;

    for (unsigned i = 0; i != TEXT_DIGITS.size(); ++i)
    {
        auto val = line.find(TEXT_DIGITS[i]);
        if (val != std::string::npos && val < minIdx)
        {
            minIdx = val;
            minDigit = i % 10;
        }
    }
    return minDigit;
}

unsigned find_last_digit(std::string const &line)
{
    unsigned maxIdx = 0;
    unsigned maxDigit = 0;

    for (unsigned i = 0; i != TEXT_DIGITS.size(); ++i)
    {
        auto val = line.rfind(TEXT_DIGITS[i]);
        if (val != std::string::npos && val > maxIdx)
        {
            maxIdx = val;
            maxDigit = i % 10;
        }
    }

    return maxDigit;
}

unsigned parse_line(std::string const &line)
{
    auto first = find_first_digit(line);
    auto last = find_last_digit(line);
    std::cout << (first * 10 + last) << '\n';
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

    unsigned total = std::accumulate(values.begin(), values.end(), 0);
    std::cout << "Calibration value: " << total << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
