// Copyright 2023 Klaas Kliffen
// SPDX-License-Identifier: Apache-2.0

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

namespace util
{
    class Line : public std::string
    {
        friend std::istream &operator>>(std::istream &is, Line &line);
    };

    std::istream &operator>>(std::istream &is, util::Line &line);

    std::ifstream open_input_stream(int argc, char *argv[]);

}

#endif // UTIL_H
