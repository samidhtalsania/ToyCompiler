#include "ParserWrapper.h"
#include "LexerFactory.h"
#include "ParserFactory.h"
#include "syntax_exception.h"


#include <iostream>
#include <string.h>
#include <stdlib.h> 
#include <stdio.h>

#include <fstream>
#include <algorithm>

#include <boost/iostreams/filtering_stream.hpp>


using namespace std;

namespace io = boost::iostreams; 




ParserWrapper::ParserWrapper(std::string file){
	
	inputFile = file;
	parser = ParserFactory::getParser(); 
  lexer = LexerFactory::getLexer();
  parser->ParseAlloc();
  
}

int ParserWrapper::parse(){
	
std::ifstream file(inputFile, std::ios_base::in | std::ios_base::binary);

  
  int hTokenId;

  
    pFile = fopen ("op.txt" , "w");
    const char* debug_prefix = "_";
    parser->ParseTrace(pFile,const_cast<char*>(debug_prefix));
  


  lexeme_t lexeme;
  std::string str;
  int lineCount = 0;
  int columnCount = 0;

  if(file){
    
    try{
      io::filtering_istream in;

      in.push(file);

      for(str; std::getline(in, str); ){
        lineCount++;
        columnCount = 0;
        if(!str.empty()){

          //Right trim the input string  
          auto it1 =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
          str.erase( it1.base() , str.end() );

          //Left trim the input tring
          auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
          str.erase( str.begin() , it2);
            

          char* buffer;
          buffer = const_cast<char*>(str.c_str());
          int len = str.size();
          lexeme.start = buffer;
          lexeme.current = buffer;
          lexeme.begin = buffer;
          // lexeme.col = 0;
          while( (hTokenId = lexer->Tokenize(buffer, len, &lexeme)) != 0 ){
            /* -1 is whitespace. Skip over whitespaces*/
            if(hTokenId != -1){
              unsigned long int pos = static_cast<unsigned long int>(lexeme.current - lexeme.start);
              string substr(lexeme.start, pos);
              Token* tok = new Token(substr);
              v.push_back(tok);
              parser->Parse(hTokenId, tok);
            }
          }
          Token* tok = new Token("0");
          parser->Parse(0, tok);
          delete tok;
          
        }
        
        else
          std::cout << "\n";        
      }

      
    
      
    }
    catch(const syntax_exception& e){
      cout<<str;/*Prints the erroneous line*/
      std::cout << e.what();
      std::cerr<<"Line:"<<lineCount<<" Column:"<<lexeme.current - lexeme.begin<<"\n";
      throw e;
    }
    catch(const std::exception& e) {
      std::cerr << e.what() << '\n';
      throw e;
    }
  }
  else{
    std::cerr << "Some error ocurred while processing this file!\n";
    return -1;
  }

  return 0;
}

// void ParserWrapper::parseComplete(){
// }

ParserWrapper::~ParserWrapper(){
	parser->ParseFree();
  LexerFactory::free();
  ParserFactory::free();
  for(auto& ve : v)
    delete ve;
	if(pFile != NULL)
		fclose(pFile);
}

// void ParserWrapper::print(std::string str){
  
// }