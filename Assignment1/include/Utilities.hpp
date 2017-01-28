#ifndef __UTILITIES_HPP_INCLUDED
#define __UTILITIES_HPP_INCLUDED

#include <iostream>
#include <cassert>
#include <memory>
#include <exception>

// Comment this out if you do not want to see debug messages.
#define __USING_DEBUGGING

// Comment this out if you do not want to use fatal error checking.
// *****************************************************************************
// * CAUTION! DISABLING FATAL ERROR CHECKING MAY RESULT IN UNDEFINED BEHAVIOR! *
// *                     * COMMENT AT YOUR OWN RISK *                          *
// *****************************************************************************
#define __USING_FATAL_ERROR_CHECKING

//****************************************************************************//
//****************************************************************************//
// Macro flags for debugging
#ifdef __USING_DEBUGGING
# define __USING_DEBUG_MACROS
#endif

#ifdef __USING_DEBUG_MACROS
# define DEBUG(x) do { std::cerr << "[ Debug ]: In function " << __func__ << ", line " << __LINE__ <<": "<< x << std::endl; } while(0)
# define DEBUG_WITH_TEST(test, message) \
		if(test) \
			DEBUG(message)

# define WARNING(x) do { std::cerr << "[ Warning ]: In function " << __func__ << ", line " << __LINE__ <<": "<< x << std::endl; } while(0)
# define WARNING_WITH_TEST(test, message) \
		if(test)\
			WARNING(message)
#else
# define DEBUG(x) do {} while(0)
# define DEBUG_WITH_TEST(a, b) do {} while(0)
# define WARNING(x) do {} while(0)
# define WARNING_WITH_TEST(a, b) do {} while(0)
#endif

// Error Handling Preprocessor Directives
#ifdef __USING_FATAL_ERROR_CHECKING
# define FATAL_ERROR_CHECK(assertion, message) \
		if(assertion) \
			std::cerr << "[ Fatal Error ]: " << message << std::endl; assert(!(assertion))
#else
# define FATAL_ERROR_CHECK(assertion, message) WARNING_WITH_TEST(assertion, message << " *ALERT* This is an uncaught fatal error! Resulting application behavior may become undefined!")
#endif

namespace jgs
{
  enum ERROR_CODE
  {
    STATUS_OK,
    STATUS_MISSING_FILE
  };

	class UnsupportedExtensionException : public std::exception
	{
		public:

			UnsupportedExtensionException(std::string extension) : theExtension(extension) {}

			const char* what() const throw ()
			{
				std::string description = "The extension " + theExtension + " for a config file is unsuported! The extension must be .conf !";
				return description.c_str();
			}

		private:
			std::string theExtension;
	};

	class MissingConfigurationElementException : public std::exception
	{
		public:

			MissingConfigurationElementException(std::string element) : theElement(element) {}

			const char* what() const throw()
			{
				std::string description = "The configuration element " + theElement + " is missing from the configuration file!";
				return description.c_str();
			}

		private:

			std::string theElement;
	};

}

#endif
