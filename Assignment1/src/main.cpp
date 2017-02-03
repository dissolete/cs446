#include "Utilities.hpp"
#include "Parser.hpp"
#include "Substring.hpp"

int main(int argc, char ** argv)
{
  using namespace jgs;
  
  // Abort if user did not supply a config file!
  FATAL_ERROR_CHECK(argc <= 1, "A configuration file must be supplied for proper simulation!");

  Parser parser;


  if(not parser.parse(argv[1]))
  {
	  std::cout << "+-----------------------------------------------------------------------------+" << std::endl;
	  std::cout << "One or more errors occured while attempting to parse the configuration files!\n"
			    << "Error(s): ";
	  std::cout << parser.get_error() << std::endl;
	  std::cout << "+-----------------------------------------------------------------------------+" << std::endl;
	  return -1;
  }
  
  return 0;

}
