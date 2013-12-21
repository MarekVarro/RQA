/*
	Program			: RQ_Analyzer 
	Date Created	: 10.07.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ lexer and syntax analyzer.
*/

//STL Includes
#include	<iostream>
#include	<fstream>
#include	<map>
#include	<stack>

//RQA Includes
#include <Parser.h>
#include <Lexer.h>

int main(int argc, char* argv[]) {
	/*
	FILE* rq_in;
	char location[100];
	
	
	cout << "Please enter a file location without any spaces:" << endl;
	cin >> location;

	if ((rq_in = fopen(location, "r")) == NULL) {
		cout << "ERROR: File could not open!\nProgram terminated." << endl;
		exit(404);
	}

	Lexer myLex = Lexer(rq_in);
	myLex.driver();
	*/

	Parser rq_analyzer = Parser();
	rq_analyzer.parse();

	return 0;
}