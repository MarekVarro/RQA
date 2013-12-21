/*
	Program			: RQ_Analyzer 
	Date Created	: 10.07.2013	(mm.dd.yyyy)
	Last Updated	: 10.16.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ terminal and non-terminal symbols enumerated type.
*/

enum Symbol
{
//Special Symbols:
	ERROR,				// You done goofed

//Terminal Symbols:
	TS_L_PARENS,		// '('
	TS_R_PARENS,		// ')'
	TS_ANDIS_OP,		// "&:"
	TS_CMD_TERM,		// '!'
	TS_COMMA,			// ','
	TS_L_CARROT,		// '<'
	TS_R_CARROT,		// '>'
	TS_PRGM_MAIN,		// "MAIN"
	TS_PRGM_END,		// "QUIT!"
	TS_ID,				// <identifier> (evaluated)
	TS_INTEGER,			// <integer> (evaluated)
	TS_EOF,				// EOF

	//Function related terminals
	TS_F_DEF,			// "DECLARE"
	TS_F_TYPE_DEF,		// "TYPE"
	TS_F_ARG_DEF,		// "TAKES"
	TS_F_RETURN,		// "GIVES"
	TS_F_ARGS,			// "ARGUE"

	//Operation related terminals
	TS_WHILE_COND,		// "WHILE"
	TS_REP_STMT,		// "REPEAT"
	TS_IF_COND,			// "IF"
	TS_DO_STMT,			// "DO"

	//Math Operators
	TS_PLUS_OP,			// "ADD"
	TS_SUB_OP,			// "SUBTRACT"
	TS_MULT_OP,			// "MULTIPLY"
	TS_DIV_OP,			// "DIVIDE"
	TS_EXP_OP,			// "EXPONENTIATE"

	//Relational Operators
	TS_ASSIGN_OP,		// "IS"
	TS_EQUIV_OP,		// "EQUALS"
	TS_LESS_OP,			// "LESS"
	TS_GREATER_OP,		// "GREATER"
	TS_LESSEQUAL_OP,	// "LESSEQUAL"
	TS_GREATEREQUAL_OP, // "GREATEREQUAL"
	TS_NOT_OP,			// "NOT"

	//Type terminals
	TS_NOTHING,			// "NOTHING"

//Non-Terminal Symbols:
	//Program non-terminals
	NTS_PROGRAM,				// <program>, the start symbol

	//Function non-terminals
	NTS_F_DECLARATION_SECTION,	// <function_declaration_section>
	NTS_F_DECLARATION,			// <function_declaration>
	NTS_F_HEADER,				// <function_header>
	NTS_F_FPARAM_LIST,			// <formal_parameter_list>
	NTS_F_BODY,					// <function_body>
	NTS_F_RETURN,				// <return_statement>
	NTS_F_DESIGNATOR,			// <function_designator>
	NTS_F_ARG_LIST,				// <argument_list>

	//Operation non-terminals
	NTS_OPERATION_SECTION,		// <operation_section>
	NTS_OPERATION,				// <operation>
	NTS_ASSIGNMENT,				// <assignment>
	NTS_STRUCTURED_OP,			// <structured_operation>
	NTS_WHILE,					// <while_structure>
	NTS_IF,						// <if_structure>

	//Expression non-terminals
	NTS_EXPRESSION,				// <expression>
	NTS_SIMPLE_EXPRESSION,		// <simple_expression>
	NTS_TERM,					// <term>
	NTS_FACTOR,					// <factor>

	//Other non-terminals
	NTS_RELATIONAL_OPS,			// <relational_operator>
	NTS_ADDITION_OPS,			// <addition_operator>
	NTS_MULTIPLICATION_OPS,		// <multiplication_operator>

	NTS_TYPE					// <type>
};