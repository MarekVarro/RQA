/*
	Program			: RQ_Analyzer 
	Date Created	: 10.16.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ Lexical Analyzer.
*/

#pragma		once
#include	<rq_consts.h>
#include	<Token.h>

class Lexer {
private:
	CharClass charClass;
	Token nextToken;
	char nextChar;
	FILE* rq_in;
	Keywords keywords;

public:
	Lexer(FILE* in);
	~Lexer();

	Token lex();

	void driver();

	//void setIn(FILE* in);
	void resolve();
	void lookup(char c);
	void addChar();
	void getChar();
	void getNonBlank();
};