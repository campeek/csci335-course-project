#pragma once

/* parser.hpp
 * Cameron Peek
 * 9/12/26
 *
 **/

#include "opcode.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

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

extern std::unordered_map<std::string, OpCode> optab;
SourceLine parseLine(std::string line);
int readAsm(std::string filename);
