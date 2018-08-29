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

class Lexer {
	std::string text;
	int pos;
	char current_char;

	void advance();
	void skip_whitespace();
	void error(std::string msg="Lexer error occured");

public:
	Token peek();
	int integer();
	Token * get_next_token();
	bool end_of_text();
	Lexer(std::string text); 
};

class Interpreter {
	std::string text;
	int pos;
	Token * current_token;
	Lexer lex;

	float term();
	float factor();
public:

	Interpreter(std::string text);
//	Token * get_next_token();
	void eat(token_t type);
	void error(std::string msg = "Interpreter error occured");
//	bool end_of_text();

	float expr();
};

