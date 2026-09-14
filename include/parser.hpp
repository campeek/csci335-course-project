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

