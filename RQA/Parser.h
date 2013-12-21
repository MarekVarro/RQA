/*
	Program			: RQ_Analyzer 
	Date Created	: 10.17.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ parser.
*/

#include	<rq_consts.h>
#include	<Lexer.h>
#include	<stack>
#include	<map>

class Parser {
private:
	map<Symbol, map<Symbol, int>> table;
	stack<Symbol> ss;
	Token token;

public:
	Parser();
	~Parser();

	void parse();
};