#include "PrevotyLexer.h"
#include "syntax_exception.h"

int PrevotyLexer::Tokenize(const char * YYCURSOR, int len , lexeme_t* lexeme)
{

 	if (lexeme->current >= (YYCURSOR + len)) {
        return 0;
    }
    lexeme->start = lexeme->current;

    const char * YYMARKER;
	#define YYCURSOR lexeme->current

	/*!re2c
		WS						= [ \t\v\f];
		
		'\000'              	{ return 0; }
		
		[-]?([0-9]+[.]{1}[0-9]+|[0-9]+)
								{ return NUMBER; }
		"let"					{ return LET; }
		["a-zA-Z]+[a-zA-Z0-9"]*	{ return STRING; }
		
		"="						{ return EQUAL; }
		"+"						{ return PLUS; }
		"-"						{ return MINUS; }
		"/"						{ return DIV; }
		"*"						{ return MUL; }
		">"						{ return GRT; }
		"<"						{ return LST; }

		"("						{ return LPAREN; }
		")"						{ return RPAREN; }


		"true"					{ return TRUE; }
		"false"					{ return FALSE; }
		
		
		WS						{ return -1; }
		
		*						{
									std::string str(--lexeme->current,0,1);
									throw syntax_exception("Syntax Error - Unexpected "+ str +"\n");
								}
								
	*/

}