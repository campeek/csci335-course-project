#pragma once
/* program.hpp
*  Cameron Peek
*  9/22/16
*
*/

#include <vector>
#include <unordered_map>
#include "parser.hpp"


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

struct Program{
    std::vector<SourceLine> sourceLines;
    std::unordered_map<std::string, int> symtab;
    int programLength;
    int startCtr;
};
