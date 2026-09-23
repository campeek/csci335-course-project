/* parser.cpp
 * Cameron Peek
 * 9/13/26
 *
 **/

#include "parser.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

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
    {"FIX",     {0xC4, 1}},
};

std::unordered_map<std::string, int> symtab = {};
std::unordered_map<std::string, Literal> littab = {};

int start_addr = 0;
int cur_addr = 0;

SourceLine parseLine(std::string line) {

    // if line doesn't have a label, it has to start with a space
    bool hasLabel = !line.empty() && !std::isspace(static_cast<unsigned char>(line[0]));
    std::istringstream iss(line);

    SourceLine thisLine;

    std::string label;
    std::string mnem;
    std::string operand;
    int addr;
    OpCode opcode;

    // grab label if it exists
    if(hasLabel) {
        iss >> label >> mnem;
    } else {
        iss >> mnem;
    }

    iss >> operand;

    thisLine.raw = line;
    thisLine.address = cur_addr;
    thisLine.label = label;

    if(hasLabel){
        symtab[label] = cur_addr;
    }

    if(mnem == "START"){
        if(start_addr == 0){
            start_addr = std::stoi(operand, nullptr, 16);
            cur_addr = start_addr;
        } else {
            //TODO: handle error here
        }
    } else if (mnem == "WORD"){ // word literal - 3 bytes 
        cur_addr += 3;
    } else if(mnem == "RESW"){ // reserve word - 3 bytes * operand (num words) 
        cur_addr += 3*std::stoi(operand, nullptr, 16);
    } else if(mnem == "RESB"){ // reserve byte - operand
        cur_addr += std::stoi(operand);
    } else if(mnem == "BYTE"){ // byte literal  - however long op is, but in bytes
        cur_addr += byteLength(operand);
    } else if(mnem == "BASE"){ // tell assembler what's in B reg, useless to us rn
        // :)
    } else if(mnem == "NOBASE"){ // stop using base addressing, also useless rn
        // :(
    } else if(mnem == "END"){ // just store the operand for pass 2 to deal with
        thisLine.operand = operand;
    } else if(mnem == "EQU"){ // constant def - add to symtab
        // wait, wouldn't it already be there? since it has a label??
    } else {

        // check for leading + for format 4
        bool extended = !mnem.empty() && mnem[0] == '+';
        if(extended) mnem.erase(0,1); // cut off the + cuz it'll mess up the lookup

        // grab opcode from map
        opcode = optab.at(mnem);

        // generate SourceLine struct
        thisLine.raw = line;
        thisLine.address = cur_addr;
        thisLine.label = label;
        thisLine.operand = operand;
        thisLine.mnemonic = mnem;
        thisLine.opcode = opcode;

        int format = opcode.format;
        if(extended) format++; // format 4 takes 4 bytes
        
        // thrugh incredible provenance, the format number is also the length of the instruction.
        cur_addr += format;
    }



    std::cout << "parsed line -> ";
    if(hasLabel) {
        std::cout << "label: " << label;
    } else {
        std::cout << "label:    ";
    }

    std::cout << " mnem: " << mnem << " operand: " << operand << " opcode: " << opcode << " address: 0x" << std::hex << std::uppercase << thisLine.address << std::dec << "\n";
    return thisLine; 
}

Program readAsm(std::string fileName){
    std::ifstream file(fileName);

    if(!file.is_open()){
        std::cerr << "Couldn't open file\n";
        return Program{}; // heres a grenade i pulled the pin for you :))
    }

    std::string line;
    Program prog;

    while(std::getline(file, line)){
        prog.sourceLines.push_back(parseLine(line));
    }

    std::cout << "generated symtable:\n";
    for(const auto& [sym, addr] : symtab){
        std::cout << sym << " : 0x" << std::hex << std::uppercase << addr << std::dec << "\n";
    }

    file.close();
    return prog;
}

int byteLength(std::string op){
    // BYTE reserves a byte literal
    // we need to know what kind and how big it is

    // pull type from first char of string
    // ditch the ' and return what's left for byte size
    char type = op[0];
    if(type == 'C'){
        return op.length() - 3;
    } else if (type == 'X'){
        // each pair of hex digits is 1 byte
        // X can't be half byte. validate.
        int bytes = op.length() - 3;
        if(bytes % 2 == 0){
            return (op.length() - 3) / 2;
        } else {
            //TODO: start flipping the fuck out
            return 0;
        }
    } else {
        //TODO: error handling
        return 0;
    }
}
