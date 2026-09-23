/* literal.hpp
*  Cameron Peek
*  9/23/26
*
*/

#pragma once

#include <cstdint>

struct Literal {
    uint8_t address;
    uint8_t value;
};

bool hasAddress(Literal* literal){
    if (literal -> address != nullptr){
        return true;
    }
    return false;
}
