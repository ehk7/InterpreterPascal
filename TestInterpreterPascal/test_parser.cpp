#include "pch.h"

#include "../InterpreterPascal/parser.h"



TEST(Lexer, end_of_text) {
	std::string text = "";
	Token(int_t, 5);
	EXPECT_NO_THROW(text == "");
	Lexer lex(text);
	EXPECT_TRUE(lex.end_of_text());


	text = "4+5-2*6+3/9";
	EXPECT_NO_THROW(lex=Lexer(text));
	int i = 0;
	while (!lex.end_of_text()) {
		lex.get_next_token();
		i++;
	}
	EXPECT_EQ(i, 11);
}

TEST(Lexer, get_next_token_no_spaces) {
	std::string text = "44+5-2*6+3/9";
	std::string tokens[11] = { "44","+" , "5", "-", "2", "*", "6", "+", "3", "/", "9" };
	Lexer lex(text);
	Token * t = NULL;
	int i = 0;
	token_t type = int_t;
	while (!lex.end_of_text()) {
		t = lex.get_next_token();
		EXPECT_EQ(t->type, type);
		EXPECT_EQ(t->value, tokens[i]);
		if (type == int_t)
			type = op_t;
		else
			type = int_t;
		i++;
	}
}

TEST(Lexer, get_next_token_spaces) {
	std::string text = "44+  5    -2*6 +3/9";
	std::string tokens[11] = { "44","+" , "5", "-", "2", "*", "6", "+", "3", "/", "9" };
	Lexer lex(text);
	Token * t = NULL;
	int i = 0;
	token_t type = int_t;
	while (!lex.end_of_text()) {
		t = lex.get_next_token();
		EXPECT_EQ(t->type, type);
		EXPECT_EQ(t->value, tokens[i]);
		if (type == int_t)
			type = op_t;
		else
			type = int_t;
		i++;
	}
}

TEST(Interpreter, factor_basic) {
	std::string exp = "55*7";
	Interpreter intp(exp);
	EXPECT_EQ(intp.expr(), 385);
	intp = Interpreter("0*434");
	EXPECT_EQ(intp.expr(), 0);
	intp = Interpreter("6*44");
	EXPECT_EQ(intp.expr(), 264);

}

TEST(Interpreter, factor_full) {
	std::string exp = "55*7/5";
	Interpreter intp(exp);
	EXPECT_EQ(intp.expr(), 77);
	intp = Interpreter("434/-2*10");
	EXPECT_EQ(intp.expr(), -2170);
	intp = Interpreter("6/6*44*0");
	EXPECT_EQ(intp.expr(), 0);

}

TEST(Interpreter, term_basic) {
	std::string exp = "55+7";
	Interpreter intp(exp);
	EXPECT_EQ(intp.expr(), 62);
	intp = Interpreter("0-434");
	EXPECT_EQ(intp.expr(), -434);
	intp = Interpreter("6-44");
	EXPECT_EQ(intp.expr(), -38);
}

TEST(Interpreter, term_full) {
	std::string exp = "55+7-78";
	Interpreter intp(exp);
	EXPECT_EQ(intp.expr(), 16);
	intp = Interpreter("-0-434");
	EXPECT_EQ(intp.expr(), -434);
	intp = Interpreter("-6+44");
	EXPECT_EQ(intp.expr(), 38);
}

TEST(Interpreter, expr) {
	std::string exp = "55*7+5-3";
	Interpreter intp(exp);
	EXPECT_EQ(intp.expr(), 387);
	intp = Interpreter("12*32+88*0-100");
	EXPECT_EQ(intp.expr(), 284);
	intp = Interpreter("-3+6*44-100*2");
	EXPECT_EQ(intp.expr(), 61);
}

TEST(Interpreter, expr_with_bracket) {
	std::string exp = "55*(7+5)-3";
	Interpreter intp(exp);
	EXPECT_EQ(intp.expr(), 657);
	intp = Interpreter("(12*32)+88*(0-(100))");
	EXPECT_EQ(intp.expr(), -8416);
	intp = Interpreter("(-3+6)*44-100");
	EXPECT_EQ(intp.expr(), 32);
}