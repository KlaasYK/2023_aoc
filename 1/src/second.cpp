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

namespace util
{
    class Line : public std::string
    {
        friend std::istream &operator>>(std::istream &is, Line &line)
        {
            return std::getline(is, line);
        }
    };

}

std::ifstream open_input_stream(int argc, char *argv[])
{
    if (argc < 2)
    {
        throw std::runtime_error("No input file provided");
    }
    return std::ifstream(argv[1]);
}

unsigned find_first_digit(unsigned &idx, std::string const &line)
{
    for (unsigned i = 0; i != line.size(); ++i)
        if (std::isdigit(line[i]))
        {
            idx = i;
            return line[i] - '0';
        }
    return 0;
}

// Use zero to make sure that idx equals value
std::vector<std::string> const TEXT_DIGITS({"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"});

unsigned find_first_text_digit(unsigned &idx, std::string const &line)
{
    unsigned minIdx = std::numeric_limits<unsigned>::max();
    unsigned minDigit = 0;

    for (unsigned i = 1; i != 10; ++i)
    {
        auto val = line.find(TEXT_DIGITS[i]);
        if (val != std::string::npos && val < minIdx)
        {
            minIdx = val;
            minDigit = i;
        }
    }

    idx = minIdx;
    return minDigit;
}

unsigned find_last_text_digit(unsigned &idx, std::string const &line)
{
    unsigned maxIdx = 0;
    unsigned maxDigit = 0;

    for (unsigned i = 1; i != 10; ++i)
    {
        auto val = line.rfind(TEXT_DIGITS[i]);
        if (val != std::string::npos && val > maxIdx)
        {
            maxIdx = val;
            maxDigit = i;
        }
    }

    idx = maxIdx;
    return maxDigit;
}

unsigned parse_line(std::string const &line)
{
    // find first digit
    unsigned idx_first_real_digit = std::numeric_limits<unsigned>::max();
    auto first_real_digit = find_first_digit(idx_first_real_digit, line);

    // find second digit (reversed)
    std::string reversed(line.rbegin(), line.rend());
    unsigned idx_last_real_digit = 0;
    auto last_real_digit = find_first_digit(idx_last_real_digit, reversed);
    // idx is reversed too, do make sure it is not the max!
    idx_last_real_digit = last_real_digit != 0 ? line.size() - idx_last_real_digit : 0;

    // look for text digits
    unsigned idx_first_text_digit = std::numeric_limits<unsigned>::max();
    auto first_text_digit = find_first_text_digit(idx_first_text_digit, line);

    unsigned idx_last_text_digit = 0;
    auto last_text_digit = find_last_text_digit(idx_last_text_digit, line);

    // Check which ones to use
    unsigned first = idx_first_real_digit < idx_first_text_digit ? first_real_digit : first_text_digit;
    unsigned last = idx_last_real_digit > idx_last_text_digit ? last_real_digit : last_text_digit;

    return first * 10 + last;
}

int main(int argc, char *argv[])
try
{
    typedef std::istream_iterator<util::Line> LineIt;

    // Read input file
    std::ifstream in(open_input_stream(argc, argv));
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
