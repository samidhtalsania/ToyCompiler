#pragma once
#include "Token.h"

class Parser
{
public:
	virtual ~Parser(){};

	virtual void Parse(int, Token*) = 0;
	virtual void ParseAlloc() = 0;
	virtual void ParseFree() = 0;
	virtual void ParseTrace(FILE*, char*) = 0;
};