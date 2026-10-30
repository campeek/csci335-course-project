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

#include <map>

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
    int locctr = 0;
    int startAddr = 0;

    std::vector<SourceLine> lines;
};

struct ControlSection {
    std::map<std::string, ProgramBlock> blocks;
    std::unordered_map<std::string, int> symtab;
    std::unordered_map<std::string, Literal> littab;

    int length = 0;
    std::string currentBlock;
};

struct Program{
    std::map<std::string, ControlSection> controlSections;
    std::string currentSection;

    Program() {
        // create a default section/block

        // you could also do this in the constructors of the structs but
        // this keeps everything in the same area.
        currentSection = "DEFAULT";

        ControlSection section{};
        section.currentBlock = "DEFAULT";
        section.blocks.emplace("DEFAULT", ProgramBlock{});

        controlSections.emplace("DEFAULT", std::move(section));
    }
};
