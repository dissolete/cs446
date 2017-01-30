#include "Utilities.hpp"
#include "Parser.hpp"
#include "StringParser.hpp"

int main(int argc, char ** argv)
{
  using namespace jgs;
  
  // Abort if user did not supply a config file!
  FATAL_ERROR_CHECK(argc <= 1, "A configuration file must be supplied for proper simulation!");

  Parser parser;

  try{
    parser.parse(argv[1]);
  }
  catch(std::string e)
  {
    std::cout << "An exception was thrown!" << std::endl;
    std::cout << e << std::endl;
  }

  return 0;

}
