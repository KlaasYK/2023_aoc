#include "common.hpp"

#include <string>

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

int is_gear_adjacent(int idx, std::vector<char> const &schematic, int width, int height)
{
    // TODO multiple gears adjacent to a single number?

    // Check top left
    if (!is_first_column(idx, width) && !is_first_row(idx, width) && schematic[idx - width - 1] == '*')
        return idx - width - 1;

    // Check top
    if (!is_first_row(idx, width) && schematic[idx - width] == '*')
        return idx - width;

    // Check top right
    if (!is_first_row(idx, width) && !is_last_column(idx, width) && schematic[idx - width + 1] == '*')
        return idx - width + 1;

    // Check left
    if (!is_first_column(idx, width) && schematic[idx - 1] == '*')
        return idx - 1;

    // Check right
    if (!is_last_column(idx, width) && schematic[idx + 1] == '*')
        return idx + 1;

    // Check bottom left
    if (!is_first_column(idx, width) && !is_last_row(idx, width, height) && schematic[idx + width - 1] == '*')
        return idx + width - 1;

    // Check bottom
    if (!is_last_row(idx, width, height) && schematic[idx + width] == '*')
        return idx + width;

    // Check bottom right
    if (!is_last_row(idx, width, height) && !is_last_column(idx, width) && schematic[idx + width + 1] == '*')
        return idx + width + 1;

    return -1;
}
