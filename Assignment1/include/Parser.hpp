#ifndef __PARSER_HPP_INCLUDED
#define __PARSER_HPP_INCLUDED

#include <string>
#include <map>
#include <fstream>
#include "Substring.hpp"
#include "Utilities.hpp"

namespace jgs
{

  class Parser
  {
    public:

	  enum State
	  {
		  BeginState, EndState, FatalState
	  };

      /**
      * Default constructor.
      */
      Parser();

      /**
      * Parses the config file. Throws an exception if there is an error in
      * the config file
      */
      bool parse(std::string configFile);

      /**
       * If an error occured, this will return the error message.
       * If no error, an empty string is returned
       */
      std::string get_error() const;

    protected:

       bool parse_config();

       State check_valid_word(std::string word);


    private:

      State m_currentState;

      std::fstream m_inf;

      std::string m_configFile, m_metaFile, m_errorString;

  };

}

#endif
