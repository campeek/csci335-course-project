#pragma once
/* program.hpp
*  Cameron Peek
*  9/22/16
*
*/

#include <vector>
#include <string>
#include <unordered_map>
#include "literal.hpp"
#include "opcode.hpp"

struct SourceLine{
	int lineNumber;

	std::string raw;

	std::string label;
    OpCode opcode;
    std::string mnemonic;
	std::string operand;
	std::string comment;

	int address = 0;
	
	std::vector<int> objectCode;
};

struct ProgramBlock {
    std::string label;

    int locctr = 0;
    int startAddr = 0;

    std::vector<SourceLine> lines;
};

struct ControlSection {
    std::string label;
    std::vector<ProgramBlock> blocks;
    std::unordered_map<std::string, int> symtab;
    std::unordered_map<std::string, Literal> littab;

    int length = 0;
    int currentBlock = 0;
};

struct Program{
    std::vector<ControlSection> controlSections;
    int activeSection = 0;
};
