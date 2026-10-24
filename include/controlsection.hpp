/* controlsection.hpp
*  Cameron Peek
*  10/15/26
*
*/

#include <unordered_map>
#include <string>
#include "literal.hpp"

extern std::unordered_map<std::string, int> symtab;
extern std::unordered_map<std::string, Literal> littab;

//TODO: map for blocks
