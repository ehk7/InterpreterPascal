#include "parser.h"

int main() {
	std::string input="hello";
	//std::cout << "\""<<input<<"\"" << input[5]<< " Length: "<<input.length() << std::endl;
	while (1) {
		std::getline(std::cin, input);
		Interpreter intp(input);
		std::cout << intp.expr() << std::endl;
	}
	system("pause");
}