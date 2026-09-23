#pragma once

/* parser.hpp
 * Cameron Peek
 * 9/12/26
 *
 **/

#include "opcode.hpp"
#include "program.hpp"
#include "literal.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

extern std::unordered_map<std::string, OpCode> optab;
extern std::unordered_map<std::string, int> symtab;
extern std::unordered_map<std::string, Literal> littab;

int byteLength(std::string op);
SourceLine parseLine(std::string line);

Program readAsm(std::string fileName);
