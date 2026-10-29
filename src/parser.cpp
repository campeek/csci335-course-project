/* parser.cpp
 * Cameron Peek
 * 9/13/26
 *
 **/

#include "parser.hpp"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <iomanip>

std::vector<SourceLine> lines;

Program curProgram;

std::unordered_map<std::string, OpCode> optab = {
    {"LDA",     {0x00, 3}},
    {"LDX",     {0x04, 3}},
    {"LDS",     {0x6C, 3}},
    {"LDT",     {0x74, 3}},
    {"STA",     {0x0C, 3}},
    {"STX",     {0x10, 3}},
    {"ADD",     {0x18, 3}},
    {"SUB",     {0x1C, 3}},
    {"COMP",    {0x28, 3}},
    {"COMPR",   {0xA0, 2}},
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

SourceLine parseLine(std::string line) {

    // all this function needs to care about is handling the incoming string
    // it doesnt modify anything "directly"

    // if line doesn't have a label, it has to start with a space
    bool hasLabel = !line.empty() && !std::isspace(static_cast<unsigned char>(line[0]));
    std::istringstream iss(line);

    // create a new SourceLine
    // we'll figure out who it belongs to later
    SourceLine thisLine;

    std::string label;
    std::string mnem;
    std::string operand;
    int addr;
    OpCode opcode;

    // grab label if it exists
    if(hasLabel) {
        iss >> label >> mnem >> operand;
    } else {
        iss >> mnem >> operand;
    }

    // we need the current programblock we're working with
    ControlSection& curSection = curProgram.controlSections.at(curProgram.activeSection);
    ProgramBlock& curBlock = curSection.blocks.at(curSection.currentBlock);

    // get the line's address from our current block's locctr
    thisLine.address = curBlock.locctr;
    thisLine.raw = line;
    thisLine.label = label;
    thisLine.mnemonic = mnem;
    thisLine.operand = operand;

    if(hasLabel){
        symtab[label] = curBlock.locctr;
    }

    if(mnem == "START"){
        if(curBlock.startAddr == 0){
            curBlock.startAddr = std::stoi(operand, nullptr, 16);
            curBlock.locctr = curBlock.startAddr;
        } else {
            //TODO: handle error here
        }
    } else if (mnem == "WORD"){ // word literal - 3 bytes 
        curBlock.locctr += 3;
    } else if(mnem == "RESW"){ // reserve word - 3 bytes * operand (num words) 
        curBlock.locctr += 3*std::stoi(operand, nullptr, 16);
    } else if(mnem == "RESB"){ // reserve byte - operand
        curBlock.locctr += std::stoi(operand);
    } else if(mnem == "BYTE"){ // byte literal  - however long op is, but in bytes
        curBlock.locctr += byteLength(operand);
    } else if(mnem == "BASE"){ // tell assembler what's in B reg, useless to us rn
        // :)
    } else if(mnem == "NOBASE"){ // stop using base addressing, also useless rn
        // :(
    } else if(mnem == "END"){ // just store the operand for pass 2 to deal with
        thisLine.operand = operand;
    } else if(mnem == "EQU"){ // constant def - add to symtab
        // wait, wouldn't it already be there? since it has a label??
    } else if(mnem == "LTORG"){
        // TODO: assign addresses to literals
    }else {

        // check for leading + for format 4
        bool extended = !mnem.empty() && mnem[0] == '+';
        if(extended) mnem.erase(0,1); // cut off the + cuz it'll mess up the lookup
        
        bool literal = !operand.empty() && operand[0] == '=';
        if(literal){
            if(hasLabel){
                uint8_t value = std::stoi(operand.erase(0,1), nullptr, 16);
                littab[label] = Literal(0x0, value);
            } else {
                // TODO: handle error
            }
        }

        // grab opcode from map
        if(optab.contains(mnem)){
            opcode = optab.at(mnem);
        } else {
            //TODO: handle error better
            std::cout << "unknown instruction: " << mnem << "\n";
        }

        // generate SourceLine struct
        thisLine.opcode = opcode;

        int format = opcode.format;
        if(extended) format++; // format 4 takes 4 bytes
        
        // thrugh incredible provenance, the format number is also the length of the instruction.
        curBlock.locctr += format;
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

    while(std::getline(file, line)){
        if(!line.empty() && line.back() == '\r'){
            line.pop_back();
        }
        parseLine(line);
    }

    std::cout << "generated symtable:\n";
    for(const auto& [sym, addr] : symtab){
        std::cout << sym << " : 0x" << std::hex << std::uppercase << addr << std::dec << "\n";
    }

    file.close();
    return curProgram;
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
