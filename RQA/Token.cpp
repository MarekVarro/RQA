/*
	Program			: RQ_Analyzer 
	Date Created	: 10.17.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ Token object.
*/

#include	<Token.h>

Token::Token() {
	lexeme.reserve(LEX_LEN);
}

Token::~Token() {
	
}

Symbol Token::getToken() {
	return token;
}

string Token::getLexeme() {
	return lexeme;
}

/* Refactor to unordered_map */
string Token::tokStr() {
	switch(token) {
	case ERROR:
		return "ERROR";
	case TS_L_PARENS:
		return "TS_L_PARENS";
	case TS_R_PARENS:
		return "TS_R_PARENS";
	case TS_ANDIS_OP:
		return "TS_ANDIS_OP";
	case TS_CMD_TERM:
		return "TS_CMD_TERM";
	case TS_PRGM_MAIN:
		return "TS_PRGM_MAIN";
	case TS_PRGM_END:
		return "TS_PRGM_END";
	case TS_ID:
		return "TS_ID";
	case TS_INTEGER:
		return "TS_INTEGER";
	case TS_EOF:
		return "TS_EOF";
	case TS_F_DEF:
		return "TS_F_DEF";
	case TS_F_TYPE_DEF:
		return "TS_F_TYPE_DEF";
	case TS_F_ARG_DEF:
		return "TS_F_ARG_DEF";
	case TS_F_RETURN:
		return "TS_F_RETURN";
	case TS_F_ARGS:
		return "TS_F_ARGS";
	case TS_WHILE_COND:
		return "TS_WHILE_COND";
	case TS_REP_STMT:
		return "TS_REP_STMT";
	case TS_IF_COND:
		return "TS_IF_COND";
	case TS_DO_STMT:
		return "TS_DO_STMT";
	case TS_PLUS_OP:
		return "TS_PLUS_OP";
	case TS_SUB_OP:
		return "TS_SUB_OP";
	case TS_MULT_OP:
		return "TS_MULT_OP";
	case TS_DIV_OP:
		return "TS_DIV_OP";
	case TS_EXP_OP:
		return "TS_EXP_OP";
	case TS_ASSIGN_OP:
		return "TS_ASSIGN_OP";
	case TS_EQUIV_OP:
		return "TS_EQUIV_OP";
	case TS_LESS_OP:
		return "TS_LESS_OP";
	case TS_GREATER_OP:
		return "TS_GREATER_OP";
	case TS_LESSEQUAL_OP:
		return "TS_LESSEQUAL_OP";
	case TS_GREATEREQUAL_OP:
		return "TS_GREATEREQUAL_OP";
	case TS_NOT_OP:
		return "TS_NOT_OP";
	case TS_NOTHING:
		return "TS_NOTHING";
	case TS_L_CARROT:
		return "TS_L_CARROT";
	case TS_R_CARROT:
		return "TS_R_CARROT";
	default:
		return "unexpected case";
	}
}

void Token::setToken(Symbol tok) {
	token = tok;
}

void Token::addChar(char c) {
	if (lexeme.length() < LEX_LEN )
		lexeme+= c;
	else
		printf("ERROR: Lexeme is too long!\n");
}

void Token::clearLexeme() {
	lexeme.clear();
	lexeme.reserve(LEX_LEN);
}

/* TODO: Add in print formatting */
void Token::print() {
	cout << "Token is: " + tokStr() + ", Lexeme is: " + lexeme << endl;
}