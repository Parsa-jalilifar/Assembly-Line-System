// Name: Parsa Jalilifar
// Seneca Student ID: 133308189
// Seneca email: pjalilifar@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include <vector>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 0;

// Default constructor

CustomerOrder::CustomerOrder()
{
	m_name = "";
	m_product = "";
	m_cntItem = 0;
	m_lstItem = nullptr;
}

// A constructor with one argument

CustomerOrder::CustomerOrder(const std::string& strCustomerOrder)
{
	Utilities temp;
	bool ok = true;
	size_t pos = 0;

	// extract and store name of customer

	m_name = temp.extractToken(strCustomerOrder, pos, ok);

	// extract and store name of product

	m_product = temp.extractToken(strCustomerOrder, pos, ok);

	// extract and store names of orders

	m_cntItem = std::count(strCustomerOrder.begin(), strCustomerOrder.end(), temp.getDelimiter()) - 1;
	m_lstItem = new ItemInfo * [m_cntItem];

	for (size_t i = 0; i < m_cntItem; i++)
	{
		std::string nameToken = temp.extractToken(strCustomerOrder, pos, ok);
		m_lstItem[i] = new ItemInfo(nameToken);
	}

	if (m_widthField < temp.getFieldWidth()) {
		m_widthField = temp.getFieldWidth();
	}
}

// Copy constructor

CustomerOrder::CustomerOrder(const CustomerOrder& customer)
{
	throw "don't copy";
}

// Move constructor

CustomerOrder::CustomerOrder(CustomerOrder&& customer) noexcept
{
	m_lstItem = nullptr;
	*this = std::move(customer);
}

// Move assignment operator

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& customer)
{
	if (this != &customer)
	{
		m_name = customer.m_name;
		m_product = customer.m_product;
		m_cntItem = customer.m_cntItem;

		delete[] m_lstItem;
		m_lstItem = customer.m_lstItem;
		customer.m_lstItem = nullptr;
		customer.m_cntItem = 0;
	}
	return *this;
}

// Destructor

CustomerOrder::~CustomerOrder()
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
}

// it returns the ItemInfo::m_fillState of the item specified as a parameter

bool CustomerOrder::getItemFillState(std::string itemName) const
{
	bool status = true;

	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_itemName == itemName)
		{
			status = m_lstItem[i]->m_fillState;
		}
	}

	return status;
}
// it returns true if all the items in the order have been filled; false otherwise

bool CustomerOrder::getOrderFillState() const
{
	bool status = true;
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_fillState == false)
		{
			status = false;
			break;
		}

	}
	return status;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os)
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (item.getName() == m_lstItem[i]->m_itemName)
		{
			if (item.getQuantity() != 0)
			{
				item.updateQuantity();
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;

				os << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else
			{
				os << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}

		}
	}
}

void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; i++)
	{
		os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] "
			<< std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";

		if (m_lstItem[i]->m_fillState)
		{
			os << "FILLED";
		}
		else
		{
			os << "MISSING";
		}
		os << std::endl;
	}
}

