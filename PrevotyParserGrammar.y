%include 
{
	#include <iostream>
	#include <assert.h> 
	#include <stdio.h>
	#include <string.h>
	#include <memory>
	#include <map>
	#include <set>
	#include <string>
	#include <algorithm>
	#include <sstream>
	
	#include "Token.h"
	#include "Base.h"

	#include "syntax_exception.h"


	using namespace std;

	#define SPACE " "
	

	#define YYNOERRORRECOVERY 
	#undef YYERRORSYMBOL

	struct cmp{
		bool operator()(const std::pair<std::string, std::string>& left, const std::pair<std::string, std::string>& right) const{
			return left.first < right.first;
		}
	};

	enum operators {eq, pl, mi, di, mu, grt, lst};

	std::map<std::string, int> mapVal;

	 int compute(int num1, int num2, operators op){
		int val = 0;
		switch(op){
			case pl:
				val = num1 + num2;
				break;
			case mu:
				val = num1 * num2;
				break;
			case di:
				if(num2 == 0)
					throw syntax_exception("\nError: Division by zero.\n");
				val = num1 / num2;
				break;
			case mi:
				val = num1 - num2;
				break;
			default:
				val = 0;
		}
		return val;
	}

	 bool computeBool(int num1, int num2, operators op){
		bool ret = false;
		switch(op){
		case eq:
			ret = num1 == num2;
			break;
		case grt:
			ret = num1 > num2;
			break;
		case lst:
			ret = num1 < num2;
			break;
		default:
			ret = false;
		}
		return ret;

	}

	 

	 bool computeBool(bool num1, bool num2){
		
		return num1 == num2;
	}

}

%name PrevotyParserGrammar
%start_symbol start

%parse_accept {
	
		//std::cout<<("%parsing complete!\n");
	}

%parse_failure 
{
    std::cout<<"Giving up.Parser is lost...\n";

}

%syntax_error{
	 // std::cout << ;
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
            int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
            if (a < YYNSTATE + YYNRULE) {
                    // std::cout << "expected " << yyTokenName[i] << std::endl;
            		// yy_parse_failed(yypParser);
                    throw syntax_exception("Syntax Error - Expected " + std::string(yyTokenName[i]) + " Found " + std::string(yyTokenName[yymajor])
+ "\n");
            }
    }
    throw syntax_exception("Parsing Failed. Unexpected sequence of tokens\n");
    
}


%token_type {Token*}
%type base {Base*}
%type start {Base*}
%type parent {Base*}
%type child{Base*}
%type boole{bool}
%type op{operators}
%type num{int}


start(S) ::= parent(P). { S = P;
	if(S->hasBooleanValue()){
		std::cout << S->getBoolString() << "\n";
	}
	else{
		std::cout << S->getValue() << "\n";	
	}
 }

parent(P) ::= LPAREN child(C) RPAREN. { P = C;}

child(C) ::= base(B). { C =B;}

base(B) ::= LPAREN base(B1) RPAREN.{
	B = B1;
}

base(B) ::= op(O) num(N) num(N1).{
	if(O == eq || O == grt || O == lst)
		B = new Base(computeBool(N, N1, O));
	else
		B = new Base(compute(N, N1, O));
}

base(B) ::= op(O) base(B1) base(B2).{
	if(B1->hasBooleanValue() || B2->hasBooleanValue()){
		B = new Base(computeBool(B1->getBooleanValue(), B2->getBooleanValue()));
	}
	else{
		if(O == lst || O == grt)
			B = new Base(computeBool(B1->getValue(), B2->getValue(), O));
		else
			B = new Base(compute(B1->getValue(), B2->getValue(), O));
	}
	delete B1, B2;
}

base(B) ::= op(O) base(B1) num(N).{
	if(O == eq || O == grt || O == lst)
		B = new Base(computeBool(B1->getValue(), N, O));
	else
		B = new Base(compute(B1->getValue(), N, O));

	delete B1;
}

base(B) ::= op(O) num(N) base(B1).{
	if(O == eq || O == grt || O == lst)
		B = new Base(computeBool(N, B1->getValue(), O));
	else
		B = new Base(compute(N, B1->getValue(), O));

	delete B1;
}

base(B) ::= LET STRING(S) num(N).{
	B = new Base(N);
	mapVal[S->toString()] = N;
} 

base(B) ::= op(O) base(B1) boole(B2).{
	B = new Base(computeBool(B1->getBooleanValue(), B2, O));
	delete B1;
}

op(O) ::= EQUAL.{
	O = eq;
}

op(O) ::= PLUS.{
	O = pl;
}

op(O) ::= MINUS.{
	O = mi;
}

op(O) ::= DIV.{
	O = di;
}

op(O) ::= MUL.{
	O = mu;
}

op(O) ::= GRT.{
	O = grt;
}

op(O) ::= LST.{
	O = lst;
}


num(N) ::= NUMBER(N1). { 
	std::stringstream num(N1->toString());
	N = 0;
	num >> N;
}

num(N) ::= STRING(S1).{
	N = mapVal[S1->toString()];
}



boole(b) ::= FALSE. { b = false; }

boole(b) ::= TRUE. { b = true; }