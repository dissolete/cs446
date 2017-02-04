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

	int string_to_int(std::string input)
	{
		int placeValue = 1;
		int result = 0;
		// Iterate to the end of the string
		int i = 0;
		while(input[i] != '\0') i++;

		// Loop backwards to create the int
		while(i >= 0)
		{
			if(input[i] == '0' or  input[i] == '1' or input[i] == '2'
				 or input[i] == '3' or input[i] == '4' or input[i] == '5' or
			 	 input[i] == '6' or input[i] =='7' or input[i] =='8' or
			 	 input[i] == '9')
			{
				result += (input[i] - '0') * placeValue;
				placeValue *= 10;
				i--;
			}
			else if(input[i] == '-')
			{
				result *= -1;
				i--;
			}
			else
			{
				std::string exception = "The input parameter " + input + " could not be converted to an int!";
				throw exception;
			}
		}
	}
}
