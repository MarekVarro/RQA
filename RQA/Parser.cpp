/*
	Program			: RQ_Analyzer 
	Date Created	: 10.17.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ parser.
*/

#include <Parser.h>

Parser::Parser() {
	ss.push(TS_EOF);
	ss.push(NTS_PROGRAM);
	

	// Program start rule
	table[NTS_PROGRAM][TS_F_DEF] = 1;

	// Function section rules
	table[NTS_F_DECLARATION_SECTION][TS_F_DEF] = 2;
	table[NTS_F_DECLARATION][TS_F_DEF] = 3;
	table[NTS_F_HEADER][TS_F_DEF] = 4;
	table[NTS_TYPE][TS_INTEGER] = 5;
	table[NTS_TYPE][TS_NOTHING] = 6;
	table[NTS_F_FPARAM_LIST][TS_NOTHING] = 7;
	table[NTS_F_FPARAM_LIST][TS_INTEGER] = 8;
	table[NTS_F_FPARAM_LIST][TS_ANDIS_OP] = 9;
	table[NTS_F_BODY][TS_F_RETURN] = 10;
	table[NTS_F_BODY][TS_ID] = 11;
	table[NTS_F_BODY][TS_WHILE_COND] = 11;
	table[NTS_F_BODY][TS_IF_COND] = 11;
	table[NTS_F_RETURN][TS_F_RETURN] = 12;
	table[NTS_F_RETURN][TS_ID] = 13;
	table[NTS_F_RETURN][TS_INTEGER] = 13;
	table[NTS_F_RETURN][TS_NOTHING] = 13;
	

	// Operation section rules
	table[NTS_OPERATION_SECTION][TS_ID] = 14;
	table[NTS_OPERATION_SECTION][TS_WHILE_COND] = 14;
	table[NTS_OPERATION_SECTION][TS_IF_COND] = 14;
	table[NTS_OPERATION_SECTION][TS_F_RETURN] = 15;
	table[NTS_OPERATION_SECTION][TS_PRGM_END] = 16;
	table[NTS_OPERATION][TS_ID] = 17;
	table[NTS_OPERATION][TS_WHILE_COND] = 18;
	table[NTS_OPERATION][TS_IF_COND] = 18;
	table[NTS_STRUCTURED_OP][TS_WHILE_COND] = 19;
	table[NTS_STRUCTURED_OP][TS_IF_COND] = 20;
	table[NTS_WHILE][TS_WHILE_COND] = 21;
	table[NTS_IF][TS_IF_COND] = 22;

	// Expression section rules
	table[NTS_EXPRESSION][TS_ID] = 23;
	table[NTS_EXPRESSION][TS_INTEGER] = 23;
	table[NTS_EXPRESSION][TS_L_PARENS] = 23;
	table[NTS_SIMPLE_EXPRESSION][TS_ID] = 24;
	table[NTS_SIMPLE_EXPRESSION][TS_INTEGER] = 24;
	table[NTS_SIMPLE_EXPRESSION][TS_L_PARENS] = 24;
	table[NTS_TERM][TS_ID] = 25;
	table[NTS_TERM][TS_INTEGER] = 25;
	table[NTS_TERM][TS_L_PARENS] = 25;
	table[NTS_FACTOR][TS_ID] = 26;
	table[NTS_FACTOR][TS_INTEGER] = 27;
	table[NTS_FACTOR][TS_L_PARENS] = 28;
	table[NTS_TERM][TS_MULT_OP] = 29;
	table[NTS_TERM][TS_DIV_OP] = 30;
	table[NTS_TERM][TS_EXP_OP] = 31;
	table[NTS_SIMPLE_EXPRESSION][TS_PLUS_OP] = 32;
	table[NTS_SIMPLE_EXPRESSION][TS_SUB_OP] = 33;
	table[NTS_EXPRESSION][TS_EQUIV_OP] = 34;
	table[NTS_EXPRESSION][TS_LESS_OP] = 35;
	table[NTS_EXPRESSION][TS_GREATER_OP] = 36;
	table[NTS_EXPRESSION][TS_LESSEQUAL_OP] = 37;
	table[NTS_EXPRESSION][TS_GREATEREQUAL_OP] = 38;
	table[NTS_EXPRESSION][TS_NOT_OP] = 39;
}

Parser::~Parser() {

}

void Parser::parse() {
	FILE* rq_in;
	char location[100];
	
	cout << "Please enter a file location without any spaces:" << endl;
	cin >> location;

	if ((rq_in = fopen(location, "r")) == NULL) {
		cout << "ERROR: File could not open!\nProgram terminated." << endl;
		exit(404);
	}
	
	Lexer lexer = Lexer(rq_in);
	lexer.getChar();

	cout << "Just initialized the lexer" << endl;


	while (!ss.empty()) {
		cout << "Just got in the while loop" << endl;
		token = lexer.lex();
		if (token.getToken() == ss.top()) {
			cout << "Matched symbols: " << token.getLexeme() << endl;
			ss.pop();
		} else {
			cout << "Rule " << table[ss.top()][token.getToken()] << endl;
			switch(table[ss.top()][token.getToken()]) {
			case 1: // Expand <program>, pop <program>
				ss.pop();
				ss.push(TS_PRGM_END);
				ss.push(NTS_OPERATION_SECTION);
				ss.push(TS_ANDIS_OP);
				ss.push(TS_PRGM_MAIN);
				ss.push(NTS_F_DECLARATION_SECTION);
				break;
			case 2: // Expand <function_declaration_section>, keep matching
				ss.push(TS_CMD_TERM);
				ss.push(NTS_F_DECLARATION);
				break;
			case 3: // Expand <function_declaration>, pop <function_declaration>
				ss.pop();
				ss.push(NTS_F_BODY);
				ss.push(TS_ANDIS_OP);
				ss.push(NTS_F_HEADER);
				break;
			case 4: // Expand <function_header>, pop <function_header>
				ss.pop();
				ss.push(NTS_F_FPARAM_LIST);
				ss.push(TS_F_ARG_DEF);
				ss.push(TS_COMMA);
				ss.push(NTS_TYPE);
				ss.push(TS_F_TYPE_DEF);
				ss.push(TS_ID);
				ss.push(TS_F_DEF);
				break;
			case 5: // Resolve <type> to "INTEGER"
				ss.pop();
				ss.push(TS_INTEGER);
				break;
			case 6: // Resolve <type> to "NOTHING"
				ss.pop();
				ss.push(TS_NOTHING);
				break;
			case 7: // Resolve <formal_parameter_list> to "NOTHING"
				ss.pop();
				ss.push(TS_NOTHING);
				break;
			case 8: // Expand <formal_parameter_list>, keep matching
				ss.push(TS_INTEGER);
				ss.push(TS_ID);
				break;
			case 9: // Terminate <formal_parameter_list>
				ss.pop();
				ss.push(TS_ANDIS_OP);
				break;
			case 10: // Expand <function_body>, pop <function_body>, resolve "GIVES"
				ss.pop();
				ss.push(NTS_F_RETURN);
				break;
			case 11: // Expand <function_body>, pop <function_body>, resolve TS_ID | TS_WHILE_COND | TS_IF_COND
				ss.pop();
				ss.push(NTS_F_RETURN);
				ss.push(NTS_OPERATION_SECTION);
				break;
			case 12: // Expand <return_statement> 
				ss.push(NTS_EXPRESSION);
				ss.push(TS_F_RETURN);
				break;
			case 13: // pop <return_statement>, resolve TS_ID | TS_INTEGER | "NOTHING"
				ss.pop();
				ss.push(NTS_EXPRESSION);
				break;
			case 14: // Expand <operation_section>
				ss.push(TS_CMD_TERM);
				ss.push(NTS_OPERATION);
				break;
			case 15: // pop <operation_section>, resolve for TS_F_RETURN 
				ss.pop();
				break;
			case 16: // pop <operation_section>, resolve for TS_PRGM_END
				ss.pop();
				ss.push(TS_PRGM_END);
				break;
			case 17: // Expand <operation>, resolve for TS_ID
				ss.pop();
				ss.push(NTS_EXPRESSION);
				ss.push(TS_ASSIGN_OP);
				ss.push(TS_ID);
				break;
			case 18: // Expand <operation>, resolve for TS_WHILE_COND | TS_IF_COND
				ss.pop();
				ss.push(NTS_STRUCTURED_OP);
				break;
			case 19: // Expand <structured_op>, resolve for TS_WHILE_COND
				ss.pop();
				ss.push(NTS_WHILE);
				break;
			case 20: // Expand <structured_op>, resolve for TS_IF_COND
				ss.pop();
				ss.push(NTS_IF);
				break;
			case 21: // Expand <while_structure>
				ss.pop();
				ss.push(TS_R_CARROT);
				ss.push(NTS_OPERATION_SECTION);
				ss.push(TS_L_CARROT);
				ss.push(TS_REP_STMT);
				ss.push(NTS_EXPRESSION);
				ss.push(TS_WHILE_COND);
				break;
			case 22: // Expand <if_structure>
				ss.pop();
				ss.push(TS_R_CARROT);
				ss.push(NTS_OPERATION_SECTION);
				ss.push(TS_L_CARROT);
				ss.push(TS_DO_STMT);
				ss.push(NTS_EXPRESSION);
				ss.push(TS_IF_COND);
				break;
			case 23: // Expand <expression> to <simple_expression>
				ss.push(NTS_SIMPLE_EXPRESSION);
				break;
			case 24: // Expand <simple_expression> to <term>
				ss.push(NTS_TERM);
				break;
			case 25: // Expand <term> to <factor>
				ss.push(NTS_FACTOR);
				break;
			case 26: // Resolve <factor> to TS_ID
				ss.push(TS_ID);
			case 27: // Resolve <factor> to TS_INTEGER
				ss.push(TS_INTEGER);
			case 28: // Resolve <factor> to "(" <expression> ")"
				ss.push(TS_R_PARENS);
				ss.push(NTS_EXPRESSION);
				ss.push(TS_L_PARENS);
				break;
			case 29: // add optional <mult_op>, <factor>
				ss.pop();
				ss.push(NTS_FACTOR);
				ss.push(TS_MULT_OP);
				break;
			case 30: // add optional <div_op>, <factor>
				ss.pop();
				ss.push(NTS_FACTOR);
				ss.push(TS_DIV_OP);
				break;
			case 31: // add optional <exp_op>, <factor>
				ss.pop();
				ss.push(NTS_FACTOR);
				ss.push(TS_EXP_OP);
				break;
			case 32: // add optional <add_op>, <term>
				ss.pop();
				ss.push(NTS_TERM);
				ss.push(TS_PLUS_OP);
				break;
			case 33: // add optional <sub_op>, <term>
				ss.pop();
				ss.push(NTS_TERM);
				ss.push(TS_SUB_OP);
				break;
			case 34: // add optional <equiv_op>, <simple_expression>
				ss.pop();
				ss.push(NTS_SIMPLE_EXPRESSION);
				ss.push(TS_EQUIV_OP);
				break;
			case 35: // add optional <equiv_op>, <simple_expression>
				ss.pop();
				ss.push(NTS_SIMPLE_EXPRESSION);
				ss.push(TS_LESS_OP);
				break;
			case 36: // add optional <equiv_op>, <simple_expression>
				ss.pop();
				ss.push(NTS_SIMPLE_EXPRESSION);
				ss.push(TS_GREATER_OP);
				break;
			case 37: // add optional <equiv_op>, <simple_expression>
				ss.pop();
				ss.push(NTS_SIMPLE_EXPRESSION);
				ss.push(TS_LESSEQUAL_OP);
				break;
			case 38: // add optional <equiv_op>, <simple_expression>
				ss.pop();
				ss.push(NTS_SIMPLE_EXPRESSION);
				ss.push(TS_GREATEREQUAL_OP);
				break;
			case 39: // add optional <equiv_op>, <simple_expression>
				ss.pop();
				ss.push(NTS_SIMPLE_EXPRESSION);
				ss.push(TS_NOT_OP);
				break;
			default:
				cout << "ERROR: Parsing table defaulted!\nDebug to observe missed case" << endl;
				exit(-1);
			}
		}
	}

	cout << "Parsing complete" << endl;
	fclose(rq_in);
}