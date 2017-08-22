#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <vector>

#include "Token.h"
#include "Parser.h"
#include "Lexer.h"

#pragma once

class ParserWrapper
{
public:
	ParserWrapper(std::string file);
	~ParserWrapper();

	int parse();

private:

	std::string inputFile;
	
	FILE* pFile;
	Parser* parser;
	Lexer* lexer;
	
	std::vector<Token*> v;
	
};