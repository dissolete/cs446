#include "Parser.hpp"

namespace jgs
{
  Parser::Parser()
  	  : m_currentState(Parser::State::BeginState)
  	  , m_errorString("")
  {}

  std::string Parser::get_error() const
  {
	  return m_errorString;
  }

  bool Parser::parse(std::string configFile)
  {

  	// Check file extension and return false if there is a mismatch
  	std::string extension = substr_from_delim(configFile, '.');
  	if( extension != "conf")
  	{
  		m_errorString += "* The extension " + extension + " is not supported by the parser! "
  					  + "The extension must be .conf";
  		return false;
  	}

  	m_configFile = configFile;

  	bool success = parse_config();

  	return success;

  }

  bool Parser::parse_config()
  {

	  // Open the config file and throw exception if it could not be opened
	  m_inf.open(m_configFile.c_str());
	  if(not m_inf.is_open())
	  {
		  m_errorString += "* The configuration file " + m_configFile
				        + " supplied cannot be opened. Does it exist?";

		  m_currentState = State::FatalState;
	  }


	  // Grab first word
	  std::string inputString;
	  m_inf >> inputString;


	  while(m_inf.good() and m_currentState != State::FatalState)
	  {
		  // Get next state
		  m_currentState = check_valid_word(inputString);


		  // Get next word
		  m_inf >> inputString;

	  }

	  m_inf.close();

	  return m_currentState == State::FatalState ? false : true;
  }

  State Parser::check_valid_word(std::string word)
  {

  }
}
