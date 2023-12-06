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

std::regex const NUMBER("\\d+");

enum MAPPING_TYPE
{
    SEED_SOIL,
    SOIL_FERT,
    FERT_WATER,
    WATER_LIGHT,
    LIGHT_TEMP,
    TEMP_HUMID,
    HUMID_LOC,
    MAPPING_TYPE_COUNT
};

struct Mapping
{
    unsigned dst;
    unsigned src;
    unsigned range;
};

std::vector<unsigned> parse_numbers(std::string const &line)
{
    std::vector<unsigned> numbers;
    auto start = std::sregex_iterator(line.begin(), line.end(), NUMBER);
    auto end = std::sregex_iterator();
    std::transform(start, end, std::back_inserter(numbers), [](auto val)
                   { return std::stoul(val.str()); });

    return numbers;
}

unsigned map(unsigned in, std::vector<Mapping> const &mapping)
{
    for (unsigned m = 0; m != mapping.size(); ++m)
        if (in >= mapping[m].src && in < mapping[m].src + mapping[m].range)
            return mapping[m].dst + in - mapping[m].src;

    return in;
}

int main(int argc, char *argv[])
try
{
    typedef std::istream_iterator<util::Line> LineIt;

    std::ifstream in(util::open_input_stream(argc, argv));
    std::vector<std::string> lines((LineIt(in)), LineIt());

    std::vector<std::vector<Mapping>> mappings(MAPPING_TYPE_COUNT, std::vector<Mapping>());

    unsigned cur_mapping = SEED_SOIL;
    for (unsigned i = 3; i != lines.size(); ++i)

        if (lines[i].ends_with(':'))
            ++cur_mapping;
        else if (lines[i].size() > 0)
        {
            auto val = parse_numbers(lines[i]);
            mappings[cur_mapping].push_back({val[0], val[1], val[2]});
        }

    auto seeds = parse_numbers(lines[0]);

    for (unsigned m = 0; m != MAPPING_TYPE_COUNT; ++m)
        for (unsigned s = 0; s != seeds.size(); ++s)
            seeds[s] = map(seeds[s], mappings[m]);

    std::cout << "min: " << *std::min_element(seeds.begin(), seeds.end()) << '\n';
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
