/* opcode.hpp
*  Cameron Peek
*  9/21/26
*
*/

#pragma once

#include <cstdint>
#include <iomanip>
#include <ostream>

struct OpCode {
    uint8_t opcode;
    int format;
};

// helper func to print opcodes. otherwise C++ sees them as literal chars and tries to convert
// the hex to ascii or unicode or whatever.

inline std::ostream& operator<<(std::ostream& os, const OpCode& op){
    os << "0x"
        << std::hex
        << std::uppercase
        << std::setw(2)
        << std::setfill('0')
        << static_cast<int>(op.opcode)
        << std::dec;

    return os;
}
