/*
	Program			: RQ_Analyzer 
	Date Created	: 10.17.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ lexical analyzer.
*/

#include	<Lexer.h>

Lexer::Lexer(FILE* in) {	
	rq_in = in;

	/* Where can I better initialize this? */
	keywords.insert(Keywords::value_type("MAIN",TS_PRGM_MAIN));
	keywords.insert(Keywords::value_type("QUIT",TS_PRGM_END));
	keywords.insert(Keywords::value_type("DECLARE",TS_F_DEF));
	keywords.insert(Keywords::value_type("TYPE",TS_F_TYPE_DEF));
	keywords.insert(Keywords::value_type("TAKES",TS_F_ARG_DEF));
	keywords.insert(Keywords::value_type("GIVES",TS_F_RETURN));
	keywords.insert(Keywords::value_type("ARGUE",TS_F_ARGS));
	keywords.insert(Keywords::value_type("WHILE",TS_WHILE_COND));
	keywords.insert(Keywords::value_type("REPEAT",TS_REP_STMT));
	keywords.insert(Keywords::value_type("IF",TS_IF_COND));
	keywords.insert(Keywords::value_type("DO",TS_DO_STMT));
	keywords.insert(Keywords::value_type("INTEGER",TS_INTEGER));
	keywords.insert(Keywords::value_type("NOTHNG",TS_NOTHING));
	keywords.insert(Keywords::value_type("ADD",TS_PLUS_OP));
	keywords.insert(Keywords::value_type("SUBTRACT",TS_SUB_OP));
	keywords.insert(Keywords::value_type("MULTIPLY",TS_MULT_OP));
	keywords.insert(Keywords::value_type("DIVIDE",TS_DIV_OP));
	keywords.insert(Keywords::value_type("EXPONENTIATE",TS_EXP_OP));
	keywords.insert(Keywords::value_type("IS",TS_ASSIGN_OP));
	keywords.insert(Keywords::value_type("EQUALS",TS_EQUIV_OP));
	keywords.insert(Keywords::value_type("LESS",TS_LESS_OP));
	keywords.insert(Keywords::value_type("GREATER",TS_GREATER_OP));
	keywords.insert(Keywords::value_type("LESSEQUAL",TS_LESSEQUAL_OP));
	keywords.insert(Keywords::value_type("GREATEREQUAL",TS_GREATEREQUAL_OP));
	keywords.insert(Keywords::value_type("NOT",TS_NOT_OP));
}

Lexer::~Lexer() {

}

/*
void Lexer::setIn(FILE* in) {
	rq_in = in;
}
*/

Token Lexer::lex() {
	nextToken.clearLexeme();
	getNonBlank();
	switch(charClass) {
	case CC_ALPHA:
		addChar();
		getChar();
		while (charClass == CC_ALPHA || charClass == CC_DIGIT) {
			addChar();
			getChar();
		}
		resolve();
		break;
	case CC_DIGIT:
		addChar();
		getChar();
		while(charClass == CC_DIGIT) {
			addChar();
			getChar();
		}
		nextToken.setToken(TS_INTEGER);
		break;
	case CC_UNKNOWN:
		lookup(nextChar);
		break;
	case CC_EOF:
		nextToken.setToken(TS_EOF);
		break;
	default:
		cout << "lex() defaulted." << endl;
	}

	nextToken.print();
	return nextToken;
}

void Lexer::resolve() { 
	unordered_map<string, Symbol>::const_iterator iter = keywords.find(nextToken.getLexeme());

	if(iter == keywords.end()) {
		nextToken.setToken(TS_ID);
		return;
	}
	nextToken.setToken(iter->second);
}

void Lexer::lookup(char c) {
	switch(c) {
	case '(':
		addChar();
		getChar();
		nextToken.setToken(TS_L_PARENS);
		break;
	case ')':
		addChar();
		getChar();
		nextToken.setToken(TS_R_PARENS);
		break;
	case '!':
		addChar();
		getChar();
		nextToken.setToken(TS_CMD_TERM);
		break;
	case ',':
		addChar();
		getChar();
		nextToken.setToken(TS_COMMA);
		break;
	case '<':
		addChar();
		getChar();
		nextToken.setToken(TS_L_CARROT);
		break;
	case '>':
		addChar();
		getChar();
		nextToken.setToken(TS_R_CARROT);
		break;
	case '-':
		addChar();
		getChar();
		if(charClass != CC_DIGIT) {
			nextToken.setToken(ERROR);
			break;
		}
		while(charClass == CC_DIGIT) {
			addChar();
			getChar();
		}
		nextToken.setToken(TS_INTEGER);
		break;
	case '&':
		addChar();
		getChar();
		if (nextChar != ':') {
			nextToken.setToken(ERROR);
		}
		addChar();
		getChar();
		nextToken.setToken(TS_ANDIS_OP);
		break;
	default:
		addChar();
		cout << "lookup() defaulted" << endl;
		nextToken.setToken(TS_EOF);
		break;
	}
	return;
}

void Lexer::addChar() {
	nextToken.addChar(nextChar);
}

void Lexer::getChar() {
	if ((nextChar = getc(rq_in)) != EOF) {
		if(isalpha(nextChar))
			charClass = CC_ALPHA;
		else if (isdigit(nextChar))
			charClass = CC_DIGIT;
		else
			charClass = CC_UNKNOWN;
	}
	else
		charClass = CC_EOF;
}

void Lexer::getNonBlank() {
	while (isspace(nextChar))
		getChar();
}

/* Used to test lexer */

void Lexer::driver() {
	getChar();
	do {
		lex();
	} while (nextToken.getToken() != TS_EOF);
}