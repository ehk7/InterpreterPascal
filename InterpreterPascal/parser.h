#include <string>
#include <sstream>
#include <iostream>
#include <ctype.h>

typedef enum { int_t, op_t, eof_t } token_t;

class Token {
public:
	token_t type;
	std::string value;

	Token(token_t type, std::string value);
	Token(token_t type, int value);
};

class Interpreter {
	std::string text;
	int pos;
	Token * current_token;
public:

	Interpreter(std::string text);
	Token * get_next_token();
	void eat(token_t type);
	void error();
	bool end_of_text();

	float expr();
	float term();
	float factor();
};

