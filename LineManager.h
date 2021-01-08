// Name: Parsa Jalilifar
// Seneca Student ID: 133308189
// Seneca email: pjalilifar@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include "Task.h"


class LineManager
{
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;

public:
	LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;

};

#endif // LINEMANAGER_H