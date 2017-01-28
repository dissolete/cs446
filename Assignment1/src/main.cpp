#include "Utilities.hpp"


int main(int argc, char ** argv)
{
  // Abort if user did not supply a config file!
  FATAL_ERROR_CHECK(argc <= 1, "A configuration file must be supplied for proper simulation!");

  return 0;
}
