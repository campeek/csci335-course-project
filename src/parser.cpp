/* parser.cpp
 * Cameron Peek
 * 9/13/26
 *
 **/

#include "parser.hpp"

#include <fstream>
#include <iostream>

std::vector<SourceLine> lines;

std::unordered_map<std::string, OpCode> optab = {
    {"LDA",     {0x00, 3}},
    {"LDX",     {0x04, 3}},
    {"STA",     {0x0C, 3}},
    {"STX",     {0x10, 3}},
    {"ADD",     {0x18, 3}},
    {"SUB",     {0x1C, 3}},
    {"COMP",    {0x28, 3}},
    {"J",       {0x3C, 3}},
    {"JEQ",     {0x30, 3}},
    {"JLT",     {0x38, 3}},
    {"JSUB",    {0x48, 3}},
    {"RSUB",    {0x4C, 3}},

    {"CLEAR",   {0xB4, 2}},
    {"TIXR",    {0xB8, 2}},
    {"ADDR",    {0x90, 2}},
};

SourceLine parseLine(std::string line) {
    bool hasLabel = !line.empty() && !std::isspace(static_cast<unsigned char>(line[0]));

    std::istringstream iss(line);

    SourceLine thisLine;

    std::string label;
    std::string mnem;
    std::string operand;
    OpCode opcode; 

    if(hasLabel) {
        iss >> label >> mnem;
    } else {
        iss >> mnem;
    }

    iss >> operand;

    opcode = optab[mnem];

    thisLine.label = label;
    thisLine.operand = operand;
    thisLine.mnemonic = mnem;
    thisLine.opcode = opcode;


    std::cout << "parsed line -> |";
    if(hasLabel) {
        std::cout << "label: " << label;
    } else {
        std::cout << "label:    ";
    }

    std::cout << " mnem: " << mnem << " operand: " << operand << " opcode: " << opcode << "\n";
    return thisLine; 
}

int readAsm(std::string fileName){
    std::ifstream file(fileName);

    if(!file.is_open()){
        std::cerr << "Couldn't open file\n";
        return 1;
    }

    std::string line;

    while(std::getline(file, line)){
//        std::cout << "Read line: " << line << "\n";
        parseLine(line);
    }

    file.close();
    return 0;
}
