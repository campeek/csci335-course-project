#pragma once
/* ControlSection.hpp
*  Cameron Peek
*  10/15/26
*
*/

#include <unordered_map>
#include "literal.hpp"
#include "program.hpp"

class ControlSection {
public:
    ProgramBlock& useBlock(const std::string& name);
    ProgramBlock& currentBlock;

    std::unordered_map<std::string, int> symtab;
    std::unordered_map<std::string, Literal> littab;

private:
    std::vector<ProgramBlock> blocks;


};
