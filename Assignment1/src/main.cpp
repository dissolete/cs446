#include "Utilities.hpp"
#include "Parser.hpp"

int main(int argc, char ** argv)
{
  using namespace jgs;
  
  // Abort if user did not supply a config file!
  FATAL_ERROR_CHECK(argc <= 1, "A configuration file must be supplied for proper simulation!");

  Parser parser;

  try{
    parser.parse("blah");
  }
  catch(std::exception & e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;

}
