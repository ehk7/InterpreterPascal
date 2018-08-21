#include "parser.h"


Token::Token(token_t type, std::string value) {
	this->type = type;
	this->value = value;
}
Token::Token(token_t type, int value) {
	this->type = type;
	this->value = std::to_string(value);
}

Interpreter::Interpreter(std::string text) {
	this->text = text;
	this->pos = 0;
	this->current_token = NULL;
}

Token * Interpreter::get_next_token() {
	std::string text = this->text;
	if (this->pos > text.length())
		return new Token(eof_t, "");


	char current_char = text[pos];

	while (isspace(current_char)) {
		pos++;
		current_char = text[pos];
	}

	//check if character is a digit
	if (48 <= current_char && 57 >= current_char) {
		int start_pos = pos;
		while (48 <= current_char && 57 >= current_char) {
			pos++;
			current_char = text[pos];
		}
		return new Token(int_t, text.substr(start_pos, pos - start_pos));
	}
	if (current_char == '+') {
		pos++;
		return new Token(op_t, "+");
	}
	else  if (current_char == '-') {
		pos++;
		return new Token(op_t, "-");
	}
	else  if (current_char == '/') {
		pos++;
		return new Token(op_t, "/");
	}
	else  if (current_char == '*') {
		pos++;
		return new Token(op_t, "*");
	}
	error();
}

void Interpreter::eat(token_t type) {
	this->current_token = this->get_next_token();
	if (this->current_token->type != type) {
		error();
	}
}

bool Interpreter::end_of_text() {
	return (this->pos >= text.length());
}

void Interpreter::error() {
	perror("error occured!\n");
	exit(0);
}

float Interpreter::expr() {
	this->eat(int_t);
	Token left = *this->current_token;
	float lv = std::stoi(left.value);
	float rv = 0;
	while (!end_of_text()) {
		this->eat(op_t);
		Token op = *this->current_token;
		this->eat(int_t);
		Token right = *this->current_token;
		rv = std::stoi(right.value);
		if (op.value[0] == '+')
			lv += rv;
		else if (op.value[0] == '-')
			lv -= rv;
		else if (op.value[0] == '/')
			lv /= rv;
		else if (op.value[0] == '*')
			lv *= rv;
	}
	return lv;
}

float Interpreter::term() {
	;
}

float Interpreter::factor() {
	;
}