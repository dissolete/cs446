#ifndef __SUBSTRING_HPP_INCLUDED
#define __SUBSTRING_HPP_INCLUDED

#include "Utilities.hpp"

namespace jgs
{

	/**
	* Returns a substring of the first characters up to a delimiter.
	* If the delimiter does not exist, the same string is returned.
	* The string returned does not include the delimiter.
	*/
	std::string substr_to_delim(const std::string & theString, char delim);

	/**
	* Returns a substring after a delim.
	* If the delim does not exist than an empty string is returned.
	*/
	std::string substr_from_delim(const std::string & theString, char delim);

	/**
	* Returns a substring between two delimiters.
	* If the either of the delimiters don't exist, then the substring after the first
	* occurance of the delimiter is returned. If neither exist, then an empty string
	* is returned.
	*/
	std::string substr_to_from_delim(const std::string & theString, char delimStart, char delimEnd);
}

#endif
