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
#include "common.hpp"

enum State
{
    START,
    PARSING_LEFT,
    PARSING_LEFT_PART,
    PARSED_LEFT_PART,
    PARSED_GEAR,
    PARSING_RIGHT,
    PARSING_RIGHT_PART
};

int main(int argc, char *argv[])
try
{
    std::vector<char> schematic;

    int width = 0;
    int height = 0;

    // Read input file
    std::ifstream in(util::open_input_stream(argc, argv));

    // Read into 2D array and find width and height
    char c;
    unsigned cur_x = 0;
    while (in.read(&c, 1))
    {
        switch (c)
        {
        case '\n':
            width = cur_x;
            cur_x = 0;
            ++height;
            break;
        default:
            ++cur_x;
            schematic.push_back(c);
        }
    }

    unsigned sum = 0;

    unsigned left = 0;
    unsigned right = 0;

    State s = START;

    for (unsigned i = 0; i != schematic.size(); ++i)
    {
        char c = schematic[i];
        // Ignore line ends
        if (c == '\n')
            continue;

        switch (s)
        {
        case START:
            if (std::isdigit(c) && is_symbol_adjacent(i, schematic, width, height))
            {
                left = c - '0';
                s = PARSING_LEFT_PART;
            }
            else if (std::isdigit(c))
            {
                left = c - '0';
                s = PARSING_LEFT;
            }
            break;

        case PARSING_LEFT:
            if (std::isdigit(c) && is_symbol_adjacent(i, schematic, width, height))
            {
                left = left * 10 + c - '0';
                s = PARSING_LEFT_PART;
            }
            else if (std::isdigit(c))
                left = left * 10 + c - '0';
            else
                s = START;
            break;

        case PARSING_LEFT_PART:
            if (std::isdigit(c))
                left = left * 10 + c - '0';
            else if (c == '*')
                s = PARSED_GEAR;
            else
                s = PARSED_LEFT_PART;
            break;

        case PARSED_LEFT_PART:
            if (std::isdigit(c))
            {
                left = c - '0';
                s = PARSING_LEFT;
            }
            else if (c == '*')
                s = PARSED_GEAR;
            break;

        case PARSED_GEAR:
            if (std::isdigit(c) && is_symbol_adjacent(i, schematic, width, height))
            {
                right = c - '0';
                s = PARSING_RIGHT_PART;
            }
            else if (std::isdigit(c))
            {
                right = c - '0';
                s = PARSING_RIGHT;
            }
            break;

        case PARSING_RIGHT:
            if (std::isdigit(c) && is_symbol_adjacent(i, schematic, width, height))
            {
                right = right * 10 + c - '0';
                s = PARSING_RIGHT_PART;
            }
            else if (std::isdigit(c))
                right = right * 10 + c - '0';
            else if (c == '*')
            {
                sum += left * right;
                left = right;
                s = PARSED_GEAR;
            }
            else
            {
                sum += left * right;
                s = START;
            }
            break;

        case PARSING_RIGHT_PART:
            if (std::isdigit(c))
                right = right * 10 + c - '0';
            else if (c == '*')
            {
                sum += left * right;
                left = right;
                s = PARSED_GEAR;
            }
            else
            {
                sum += left * right;
                left = right;
                s = PARSED_LEFT_PART;
            }
            break;
        }
        std::cout << c << ": " << s << "\tl: " << left << "\tr: " << right << "\ts: " << sum << '\n';
    }

    // Check if we ended on a partno.
    if (s == PARSING_RIGHT_PART)
        sum += left * right;

    std::cout << "sum: " << sum << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
