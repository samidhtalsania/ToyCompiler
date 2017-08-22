#include "Token.h"

#define LPAREN                           1
#define RPAREN                           2
#define LET                              3
#define STRING                           4
#define EQUAL                            5
#define PLUS                             6
#define MINUS                            7
#define DIV                              8
#define MUL                              9
#define GRT                             10
#define LST                             11
#define NUMBER                          12
#define FALSE                           13
#define TRUE                            14


#define PrevotyParserGrammarARG_PDECL
#define PrevotyParserGrammarTOKENTYPE Token*


void PrevotyParserGrammar(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  PrevotyParserGrammarTOKENTYPE yyminor       /* The value for the token */
  PrevotyParserGrammarARG_PDECL               /* Optional %extra_argument parameter */
);

void PrevotyParserGrammarTrace(FILE *TraceFILE, char *zTracePrompt);

void *PrevotyParserGrammarAlloc(void *(*mallocProc)(size_t));

void PrevotyParserGrammarFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
);


