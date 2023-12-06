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
    unsigned d;
    unsigned s;
    unsigned r;
};

struct Range
{
    unsigned s;
    unsigned r;
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
        if (in >= mapping[m].s && in < mapping[m].s + mapping[m].r)
            return mapping[m].d + in - mapping[m].s;

    return in;
}

/**
 * Maps a range in using m, with the result in mr and unmapped ranges as return value
 */
std::vector<Range> map_range(Range &mr, Range const &in, Mapping const &m)
{
    // in not in m
    if (in.s > m.s + mr.r || in.s + in.r < m.s)
    {
        mr.r = 0; // nothing mapped
        return std::vector<Range>({in});
    }

    // in completely in m
    if (in.s >= m.s && in.s + in.r <= m.s + m.r)
    {
        mr.r = in.r;
        mr.s = m.d + in.s - m.s;

        // nothing left to map
        return std::vector<Range>();
    }

    // in split by m
    if (m.s > in.s && in.s + in.r > m.s + m.r)
    {
        mr = {m.d, m.r};
        return std::vector<Range>({{in.s, m.s - in.s}, {m.s + m.r, in.s + in.r - m.s + m.r}});
    }

    // m < in
    if (m.s <= in.s && m.s + m.r > in.s && m.s + m.r < in.s + in.r)
    {
        mr = {m.d + in.s - m.s, m.s + m.r - in.s};
        return std::vector<Range>({{m.s + m.r, in.s + in.r - (m.s + m.r)}});
    }

    // m > in
    if (m.s > in.s && m.s + m.r > in.s + in.r && m.s < in.s + in.r)
    {
        mr = {m.d, in.s + in.r - m.s};
        return std::vector<Range>({{in.s, m.s - in.s}});
    }

    std::cout << "Missing something...\n";
    mr.r = 0;
    return std::vector<Range>();
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
    std::queue<Range> seed_ranges;
    for (unsigned i = 0; i < seeds.size(); i += 2)
        seed_ranges.push({seeds[i], seeds[i + 1]});

    // Part 1
    for (unsigned m = 0; m != MAPPING_TYPE_COUNT; ++m)
        for (unsigned s = 0; s != seeds.size(); ++s)
            seeds[s] = map(seeds[s], mappings[m]);

    std::cout << "min: " << *std::min_element(seeds.begin(), seeds.end()) << '\n';

    // Part 2
    for (unsigned m = 0; m != MAPPING_TYPE_COUNT; ++m)
    {
        auto mapping_list = mappings[m];
        std::vector<Range> mapped;
        for (unsigned n = 0; n != mapping_list.size(); ++n)
        {
            Range mapped_range{0, 0};
            auto mapping = mapping_list[n];
            // for (unsigned s = 0; s!= seeds.size(); ++ s)
            // {

            //     seed_ranges.pop();
            //     auto left = map_range(mapped_range, )
            // }
        }
    }
}
catch (std::exception const &ex)
{
    std::cerr << ex.what() << '\n';
    return 1;
}
