#include "Parser.hpp"

namespace jgs
{
  Parser::Parser() {}

  void Parser::parse(std::string configFile)
  {
    //throw UnsupportedExtensionException(".cnf");
    throw MissingConfigurationElementException("Processor cycle time");
  }
}
