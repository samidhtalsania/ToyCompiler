#include "ParserFactory.h"
#include "PrevotyParser.h"

Parser* ParserFactory::getParser(){
	
	PrevotyParser* par = new PrevotyParser;
	p = par;
	
	return p; 
}

void ParserFactory::free(){
	delete p;
}

Parser* ParserFactory::p;
