#include <iostream>
#include "ParserWrapper.h"


using namespace std;

int main(int argc, char **argv)
{

std::string str(argv[1]);
  ParserWrapper pw(str);
  try {
    pw.parse();
  }
  
  catch(const exception& e){
    return -1;
  }
    
  return 0;
}
