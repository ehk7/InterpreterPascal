#include "parser.h"

int main() {
	std::string input;
	while (1) {
		std::getline(std::cin, input);
		Interpreter intp(input);
		std::cout << intp.expr() << std::endl;
	}
	system("pause");
}