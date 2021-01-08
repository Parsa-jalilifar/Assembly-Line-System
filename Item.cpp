// Name: Parsa Jalilifar
// Seneca Student ID: 133308189
// Seneca email: pjalilifar@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include <iostream>
#include <iomanip>
#include "Item.h"

size_t Item::m_widthField = 1;

// default constructor 

Item::Item()
{
	m_name = "";
	m_description = "";
	m_serialNumber = 0;
	m_quantity = 0;
}

// constructor with one argument

Item::Item(const std::string & str)
{
	Utilities util;
	bool ok = true;
	size_t pos = 0;

	// extract and store name

	m_name = util.extractToken(str, pos, ok);

	// extract and store serial number

	m_serialNumber = std::stoul(util.extractToken(str, pos, ok));
	
	// extract and store serial quantity

	m_quantity = std::stoi(util.extractToken(str, pos, ok));

	if (m_widthField < util.getFieldWidth())
		m_widthField = util.getFieldWidth();

	// extract and store serial description

	m_description = util.extractToken(str, pos, ok);

	if (m_widthField > util.getFieldWidth())
		m_widthField = util.getFieldWidth();

}

// it returns the name of the current Item object

const std::string & Item::getName() const
{
	return m_name;
}

// it returns the next serial number

const unsigned int Item::getSerialNumber()
{
	return m_serialNumber++;
}

// it returns the remaining quantity of the current Item object

const unsigned int Item::getQuantity()
{
	return m_quantity;
}

// it substracts 1 from the available quantity; should not go below 0

void Item::updateQuantity()
{
	if (m_quantity > 0)
		m_quantity--;
}

// it inserts the content of the current object into first parameter

void Item::display(std::ostream & os, bool full) const
{
	os << std::left << std::setw(m_widthField);
	if (full) 
	{
		os << m_name << " [" << std::setw(6) << std::setfill('0') << std::right
			<< m_serialNumber << std::setfill(' ') << "] Quantity: "
			<< std::setw(m_widthField) << std::left << m_quantity
			<< " Description: " << m_description << std::endl;
	}
	else 
	{
		os << m_name << " [" << std::setw(6) << std::setfill('0') << std::right
			<< m_serialNumber << std::setfill(' ') << "]" << std::endl;
	}
}
