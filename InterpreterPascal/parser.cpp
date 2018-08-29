#include "parser.h"



Token::Token(token_t type, std::string value) {
	this->type = type;
	this->value = value;
}
Token::Token(token_t type, int value) {
	this->type = type;
	this->value = std::to_string(value);
}

Lexer::Lexer(std::string text) {
	this->text = text;
	this->pos = 0;
}

void Lexer::advance() {
	//handle EOF,l
}

void Lexer::skip_whitespace() {
	char current_char = text[pos];

	while (isspace(current_char)) {
		pos++;
		current_char = text[pos];
	}
}

int Lexer::integer() {
	int start_pos = pos;
	current_char = this->text[pos];
	int sign = 1;
	if (current_char == '-') {
		//sign = -1;
		pos++;
		current_char = this->text[pos];
	}
	while (48 <= current_char && 57 >= current_char) {
		current_char = text[pos];
		pos++;
	}
	pos--;
	std::string retstr = text.substr(start_pos, pos - start_pos);
	return sign*std::stoi(retstr);
}

void Lexer::error(std::string msg) {
	std::cout << msg << std::endl;
	exit(0);
}
bool Lexer::end_of_text() {
	return (this->pos >= text.length());
}

Token Lexer::peek() {
	int pos = this->pos;
	Token * next = this->get_next_token();
	Token ret = *next;
	delete next;
	this->pos = pos;
	this->current_char = this->text[pos];
	return ret;
}

Token * Lexer::get_next_token() {
	std::string text = this->text;
	if (this->pos >= text.length())
		return new Token(eof_t, "");

	this->skip_whitespace();

	char current_char = text[pos];

	//check if character is a digit
	if (48 <= current_char && 57 >= current_char) {
		return new Token(int_t, std::to_string(integer()));

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
	error("Error getting next token: unrecognised");
}

Interpreter::Interpreter(std::string text):lex(text) {
	this->text = text;
	this->pos = 0;
	this->current_token = NULL;
}

void Interpreter::eat(token_t type) {
	if (type == int_t) {
		this->current_token= new Token(int_t, lex.integer());

	}
	else {
		this->current_token = lex.get_next_token();
	}
	if (this->current_token->type != type) {
		error("Error eating!");
	}
}


void Interpreter::error(std::string msg) {
	std::cout << msg << std::endl;
	exit(0);
}

float Interpreter::expr() {
	float lv = this->term();
	Token next = lex.peek();
	while(next.value=="+" || next.value=="-") {
		this->eat(op_t);
		if (this->current_token->value == "+") {
			lv += this->term();
		}
		else if(this->current_token->value == "-") {
			lv -= this->term();
		}
		else {
			break;
		}
		next = lex.peek();
	}
	return lv;
}

float Interpreter::term() {
	float lv = this->factor();
	Token next = lex.peek();

	while(next.value=="*" || next.value=="/") {
		this->eat(op_t);
		if (this->current_token->value == "*") {
			lv *= this->factor();
		}
		else if (this->current_token->value == "/") {
			lv /= this->factor();
		}
		next = lex.peek();
	}
	return lv;
}

float Interpreter::factor() {
	this->eat(int_t);
	
	return (float)std::stoi(this->current_token->value);
}