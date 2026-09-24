/* literal.cpp
*  Cameron Peek
*  9/24/26
*
*/

#include "literal.hpp"

bool hasAddress(Literal* literal){
    if(literal -> address == 0x0){
        return true;
    }
    return false;
}
