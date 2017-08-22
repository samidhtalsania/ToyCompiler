#include "LexerFactory.h"

LexerFactory::LexerFactory(){}

Lexer* LexerFactory::getLexer(){
	PrevotyLexer* lexer = new PrevotyLexer;
	l = lexer;
	return l; 
}

void LexerFactory::free(){
	delete l;
}

Lexer* LexerFactory::l;