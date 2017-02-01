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
      void parse(std::string configFile);


    protected:

       void main_loop();


    private:

      State m_currentState;

      std::fstream m_inf;

      std::string m_configFile, m_metaFile;

  };

}

#endif
