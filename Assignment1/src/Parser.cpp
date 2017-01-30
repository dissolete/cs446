#include "Parser.hpp"

namespace jgs
{
  Parser::Parser() {}

  void Parser::parse(std::string configFile)
  {

  	// Check file extension and throw exception if there is a mismatch
  	std::string extension = substr_from_delim(configFile, '.');
  	if( extension != "conf")
  	{
  		std::string exceptionMessage = "The extension " + extension + " is not supported! " +
  		                               "The extension for the config file must be .conf";
  		throw exceptionMessage;
  	}
    //throw UnsupportedExtensionException(".cnf");
    //throw MissingConfigurationElementException("Processor cycle time");
    //throw "Test Exception";
  }
}
