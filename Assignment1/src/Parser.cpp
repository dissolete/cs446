#include "Parser.hpp"

namespace jgs
{
  Parser::Parser()
  	  :m_currentState(Parser::State::BeginState)
  {}

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


  	m_configFile = configFile;

  	main_loop();

  }

  void Parser::main_loop()
  {

	  // Open the config file and throw exception if it could not be opened
	  m_inf.open(m_configFile.c_str());
	  if(not m_inf.is_open())
	  {
		  std::string exceptionMessage = "The configuration file " + m_configFile
				                       + " supplied cannot be opened. Does it exist?";
		  throw exceptionMessage;
	  }


//	  while(m_currentState != State::EndState)
//	  {
//
//	  }

	  m_inf.close();
  }
}
