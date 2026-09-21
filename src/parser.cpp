#include "parser.hpp"

#include <fstream>
#include <iostream>

/* parser.cpp
 * Cameron Peek
 * 9/13/26
 *
 **/

std::vector<SourceLine> lines;



void parse() {


}

int readAsm(std::string fileName){
    std::ifstream file(fileName);

    if(!file.is_open()){
        std::cerr << "Couldn't open file\n";
        return 1;
    }

    std::string line;

    while(std::getline(file, line)){
        std::cout << "Read line: " << line << "\n";
    }

    file.close();
    return 0;
}
