/*
	Program			: RQ_Analyzer 
	Date Created	: 10.16.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ Token type.
*/

#pragma		once
#include	<rq_consts.h>
#include	<string>

class Token {
private:
	Symbol token;
	string lexeme;

public:
	Token();
	~Token();

	Symbol getToken();
	string getLexeme();
	string tokStr();

	void setToken(Symbol tok);
	void addChar(char c);
	void clearLexeme();
	void print();
};