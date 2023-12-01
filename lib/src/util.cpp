// Copyright 2023 Klaas Kliffen
// SPDX-License-Identifier: Apache-2.0

#include "util.hpp"
#include <fstream>

std::istream &util::operator>>(std::istream &is, util::Line &line)
{
    return std::getline(is, line);
}

std::ifstream util::open_input_stream(int argc, char *argv[])
{
    if (argc < 2)
    {
        throw std::runtime_error("No input file provided");
    }
    return std::ifstream(argv[1]);
}
