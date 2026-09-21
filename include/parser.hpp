#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

/* parser.hpp
 * Cameron Peek
 * 9/12/26
 *
 **/

struct SourceLine{
	int lineNumber;

	std::string raw;

	std::string label;
	std::string opcode;
	std::string operand;
	std::string comment;

	int address = 0;
	
	std::vector<int> objectCode;
};

void parse();
int readAsm(std::string filename);

#endif
