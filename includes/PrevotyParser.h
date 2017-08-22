#include "Parser.h"
#include "PrevotyParserGrammar.h"
#include <memory>
#include <stdlib.h> 
#pragma once

class PrevotyParser: public Parser
{
public:
	
	void Parse(int yymajor,Token* yyminor){
		PrevotyParserGrammar(parser, yymajor, yyminor);
	}

	void ParseTrace(FILE* TraceFILE, char* zTracePrompt){
		PrevotyParserGrammarTrace(TraceFILE, zTracePrompt);		
	}

	void ParseAlloc(){
		parser = PrevotyParserGrammarAlloc(malloc);
	}

	void ParseFree(){
		PrevotyParserGrammarFree(parser, free);
	}

private:
	void* parser;
};