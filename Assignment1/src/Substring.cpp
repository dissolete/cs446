#include "Substring.hpp"

namespace jgs
{

	std::string substr_to_delim(const std::string & theString, char delim)
	{
		std::string stringToReturn = "";
		
		// Iterate through the string
		for(int i = 0; i < theString.length(); ++i)
		{
			// Stop iteration if the delimiter has been reached
			if(theString[i] == delim)
				break;

			// Concatenate the string being returned with the new character
			stringToReturn += theString[i];
		}

		return stringToReturn;
	}

	std::string substr_from_delim(const std::string & theString, char delim)
	{
		std::string stringToReturn = "";

		int i = 0;

		// Move index to delim
		while(theString[i] != delim and i < theString.length()) i++;
		i++;

		// Concatenate until end of string
		while(i < theString.length())
		{ 
			stringToReturn += theString[i];
			i++;
		}

		return stringToReturn;
	}

	std::string substr_to_from_delim(const std::string & theString, char delimStart, char delimEnd)
	{
		std::string stringToReturn = "";

		int i = 0;

		// Move index to the first delim or until end of string
		while(theString[i] != delimStart and i < theString.length()) i++;
		i++;

		// Concatenate until the end delim has been reached or until end of string
		while(theString[i] != delimEnd and i < theString.length())
		{ 
			stringToReturn += theString[i];
			i++;
		}

		return stringToReturn;
	}
}
