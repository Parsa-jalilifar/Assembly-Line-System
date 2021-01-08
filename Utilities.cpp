// Name: Parsa Jalilifar
// Seneca Student ID: 133308189
// Seneca email: pjalilifar@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include "Utilities.h"

char Utilities::m_delimiter;

// it sets the field width of the current object to the value of the parameter

void Utilities::setFieldWidth(size_t wid)
{
	m_widthField = { wid };
}

// it returns the field width of the current object

size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

// it extracts tokens from the first parameter

const std::string Utilities::extractToken(const std::string & str, size_t & next_pos, bool & more)
{
	size_t next_delimiter_pos = str.find(m_delimiter, next_pos + 1);
	size_t wordLength = (next_delimiter_pos - next_pos) ;
	std::string token = str.substr(next_pos, wordLength);
	next_pos = next_delimiter_pos + 1;

	if (m_widthField < token.length())
		m_widthField = token.length();

	if (token == "")
	{
		more = false;
		throw "Error!";
	}
	else
	{
		more = true;
		return token;
	}

}

// it sets the delimiter for this class to the character received

void Utilities::setDelimiter(const char del)
{
	m_delimiter = { del };
}

// it returns the delimiter character of the current object

const char Utilities::getDelimiter() const
{
	return m_delimiter;
}
