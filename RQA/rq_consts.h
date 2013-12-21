/*
	Program			: RQ_Analyzer 
	Date Created	: 10.17.2013	(mm.dd.yyyy)
	Last Updated	: 10.17.2013	(mm.dd.yyyy)
	Authors			: Bryan Young
	Description		: RQ constant values.
*/

#pragma		once
#include	<rq_char_class.h>
#include	<rq_symbols.h>
#include	<iostream>
#include	<unordered_map>
#include	<string>
using namespace std;

#define		LEX_LEN 100

typedef unordered_map<string, Symbol> Keywords;