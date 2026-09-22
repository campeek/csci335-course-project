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

std::unordered_map<std::string, int> symtab = {};

int start_addr = 0;
int cur_addr = 0;

SourceLine parseLine(std::string line) {

    bool hasLabel = !line.empty() && !std::isspace(static_cast<unsigned char>(line[0]));
    std::istringstream iss(line);

    SourceLine thisLine;

    std::string label;
    std::string mnem;
    std::string operand;
    int addr;
    OpCode opcode;

    uint8_t instruction_length = 3; //TODO: hardcoded 3 to test. actual length varies.



    if(hasLabel) {
        iss >> label >> mnem;
    } else {
        iss >> mnem;
    }

    iss >> operand;


    //TODO: deal with other directives
    if(mnem == "START"){
        if(start_addr == 0){
            std::cout << "start op" << operand << "\n";
            start_addr = std::stoi(operand, nullptr, 16);
        } else {
            //TODO: handle error here
        }
    } else {
        opcode = optab[mnem];
        thisLine.address = cur_addr;
        thisLine.label = label;
        thisLine.operand = operand;
        thisLine.mnemonic = mnem;
        thisLine.opcode = opcode;

        if(hasLabel){
            symtab[label] = cur_addr;
        }
    }
    cur_addr += instruction_length;


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

    std::cout << "generated symtable:\n";
    for(const auto& [sym, addr] : symtab){
        std::cout << sym << " : " << addr << "\n";
    }

    file.close();
    return 0;
}
