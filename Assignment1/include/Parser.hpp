#ifndef __PARSER_HPP_INCLUDED
#define __PARSER_HPP_INCLUDED

#include <string>
#include <map>
#include "Substring.hpp"
#include "Utilities.hpp"

namespace jgs
{

  class Parser
  {
    public:

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



    private:


  };

}

#endif
