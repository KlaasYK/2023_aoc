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

#include "util.hpp"

enum State
{
    START,
    PARSING_LEFT,
    PARSED_LEFT,
    PARSED_GEAR,
    PARSING_RIGHT
};

int main(int argc, char *argv[])
try
{
    // Read input file
    std::ifstream in(util::open_input_stream(argc, argv));

    unsigned sum = 0;

    unsigned left = 0;
    unsigned right = 0;

    State s = START;

    // TODO: check that the number is a part no!

    char c;
    while (in.read(&c, 1))
    {
        // Ignore line ends
        if (c == '\n')
            continue;

        switch (s)
        {
        case START:
            if (std::isdigit(c))
            {
                left = c - '0';
                s = PARSING_LEFT;
            }
            break;

        case PARSING_LEFT:
            if (std::isdigit(c))
                left = left * 10 + c - '0';
            else if (c == '*')
                s = PARSED_GEAR;
            else if (c == '.')
                s = PARSED_LEFT;
            else
                s = START;
            break;

        case PARSED_LEFT:
            if (std::isdigit(c))
            {
                left = c - '0';
                s = PARSING_LEFT;
            }
            else if (c == '*')
                s = PARSED_GEAR;
            else if (c != '.')
                s = START;
            break;

        case PARSED_GEAR:
            if (std::isdigit(c))
            {
                right = c - '0';
                s = PARSING_RIGHT;
            }
            else if (c != '.')
                s = START;
            break;

        case PARSING_RIGHT:
            if (std::isdigit(c))
                right = right * 10 + c - '0';
            else if (c == '*')
            {
                sum += left * right;
                left = right;
                s = PARSED_GEAR;
            }
            else if (c == '.')
            {
                sum += left * right;
                left = right;
                s = PARSED_LEFT;
            }
            else
            {
                sum += left * right;
                s = START;
            }
        }
        std::cout << c << ": " << s << "\tsum:" << sum << '\n';
    }

    if (s == PARSING_RIGHT)
        sum += left * right;

    std::cout << "sum: " << sum << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
