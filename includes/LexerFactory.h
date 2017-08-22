#include "PrevotyLexer.h"

#include "Lexer.h"

#pragma once

class LexerFactory
{
public:
	LexerFactory();
	~LexerFactory();

	static Lexer* getLexer();
	static void free();

private:
	static Lexer* l;
};