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

bool is_first_column(int idx, int width)
{
    return idx % width == 0;
}

bool is_last_column(int idx, int width)
{
    return idx % width == width - 1;
}

bool is_first_row(int idx, int width)
{
    return idx - width < 0;
}

bool is_last_row(int idx, int width, int height)
{
    return idx + width >= width * height;
}

bool is_symbol(char c)
{
    return !(std::isdigit(c) || c == '.');
}

bool is_symbol_adjacent(int idx, std::vector<char> const &schematic, int width, int height)
{
    // Check top left
    if (!is_first_column(idx, width) && !is_first_row(idx, width) && is_symbol(schematic[idx - width - 1]))
        return true;

    // Check top
    if (!is_first_row(idx, width) && is_symbol(schematic[idx - width]))
        return true;

    // Check top right
    if (!is_first_row(idx, width) && !is_last_column(idx, width) && is_symbol(schematic[idx - width + 1]))
        return true;

    // Check left
    if (!is_first_column(idx, width) && is_symbol(schematic[idx - 1]))
        return true;

    // Check right
    if (!is_last_column(idx, width) && is_symbol(schematic[idx + 1]))
        return true;

    // Check bottom left
    if (!is_first_column(idx, width) && !is_last_row(idx, width, height) && is_symbol(schematic[idx + width - 1]))
        return true;

    // Check bottom
    if (!is_last_row(idx, width, height) && is_symbol(schematic[idx + width]))
        return true;

    // Check bottom right
    if (!is_last_row(idx, width, height) && !is_last_column(idx, width) && is_symbol(schematic[idx + width + 1]))
        return true;

    return false;
}

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

    std::cout << width << ' ' << height << '\n';

    unsigned sum = 0;
    unsigned cur_value = 0;
    bool can_add = false;
    // Walk through array, reading each cell
    // taking a running count of characters
    // for each digit, check if a symbol is adjacent
    // if so, add it when the number ends (i.e. a '.' is found)
    for (int i = 0; i != schematic.size(); ++i)
        if (std::isdigit(schematic[i]))
        {
            cur_value = cur_value * 10 + schematic[i] - '0';
            can_add = can_add || is_symbol_adjacent(i, schematic, width, height);
        }
        else
        {
            if (can_add)
                sum += cur_value;

            cur_value = 0;
            can_add = false;
        }

    // Check if we ended on a valid number
    if (can_add)
        sum += cur_value;

    std::cout << "sum: " << sum << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
