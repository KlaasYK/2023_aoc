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

struct Game
{
    unsigned id;
    unsigned red;
    unsigned green;
    unsigned blue;
};

unsigned constexpr MAX_RED = 12;
unsigned constexpr MAX_GREEN = 13;
unsigned constexpr MAX_BLUE = 14;

std::regex const GAME_RE("Game (\\d+):");
std::regex const SET_RE("[:;]([^:;]+)");
std::regex const COLOR_RE("(\\d+) (r|g|b)");

void parse_set(Game &g, std::string const &set)
{
    auto begin = std::sregex_iterator(set.begin(), set.end(), COLOR_RE);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        unsigned val = std::stoul((*it)[1]);
        switch ((*it)[2].str()[0])
        {
        case 'r':
            g.red = val > g.red ? val : g.red;
            break;
        case 'g':
            g.green = val > g.green ? val : g.green;
            break;
        case 'b':
            g.blue = val > g.blue ? val : g.blue;
            break;
        }
    }
}

Game parse_line(std::string const &line)
{
    Game g{0, 0, 0, 0};
    std::smatch match;

    if (std::regex_search(line, match, GAME_RE))
    {
        g.id = std::stoul(match[1]);
    }
    else
    {
        std::cout << line << '\n';
        throw std::runtime_error("Line does not match!");
    }

    auto begin = std::sregex_iterator(line.begin(), line.end(), SET_RE);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it)
        parse_set(g, (*it)[1]);

    return g;
}

int main(int argc, char *argv[])
try
{
    typedef std::istream_iterator<util::Line> LineIt;

    // Read input file
    std::ifstream in(util::open_input_stream(argc, argv));
    std::vector<std::string> lines((LineIt(in)), LineIt());

    std::vector<Game> games;
    std::transform(lines.begin(), lines.end(),
                   std::back_inserter(games),
                   parse_line);

    unsigned sum = 0;
    for (Game g : games)
    {
        std::cout << g.id << '\t' << g.red << '\t' << g.green << '\t' << g.blue << '\n';
        if (g.red <= MAX_RED && g.green <= MAX_GREEN && g.blue <= MAX_BLUE)
            sum += g.id;
    }

    std::cout << "Sum of valid games: " << sum << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
