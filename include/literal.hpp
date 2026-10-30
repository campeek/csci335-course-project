/* literal.hpp
*  Cameron Peek
*  9/23/26
*
*/

#pragma once

#include <cstdint>
#include <string>

struct Literal {
    int address = 0x0;
    std::string value;
    int length;
};

bool hasAddress(Literal& literal);