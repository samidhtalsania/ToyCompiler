#include "Parser.h"

#pragma once

class ParserFactory
{
public:
	ParserFactory();
	~ParserFactory();
	static Parser* getParser();
	static void free();

private:
	static Parser* p;
};