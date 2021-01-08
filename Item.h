// Name: Parsa Jalilifar
// Seneca Student ID: 133308189
// Seneca email: pjalilifar@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Utilities.h"

class Item
{
	std::string m_name;
	std::string m_description;
	size_t m_serialNumber;
	size_t m_quantity;
	static size_t m_widthField;

public:
	Item();
	Item(const std::string& str);
	const std::string& getName() const;
	const unsigned int getSerialNumber();
	const unsigned int getQuantity();
	void updateQuantity();
	void display(std::ostream& os, bool full) const;

};
#endif // !ITEM_H