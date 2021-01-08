// Name: Parsa Jalilifar
// Seneca Student ID: 133308189
// Seneca email: pjalilifar@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include "Task.h"

Task::Task(const std::string& strTask) : Item(strTask)
{
	m_pNextTask = nullptr;
}

void Task::runProcess(std::ostream& os)
{
	if (!m_orders.empty())
	{
		if (!m_orders.back().getItemFillState(this->getName()))
		{
			m_orders.back().fillItem(*this, os);
		}
	}
}

bool Task::moveTask()
{
	bool status = false;

	if (!m_orders.empty())
	{
		if (m_orders.back().getItemFillState(this->getName()))
		{
			m_pNextTask->operator+=(std::move(m_orders.back()));
			m_orders.pop_back();
			status = true;
		}
	}
	return status;
}

// It stores the provided Task object's reference into the m_pNextTask pointer.

void Task::setNextTask(Task& strTask)
{
	m_pNextTask = &strTask;
}

// It Removes the last CustomerOrder from the queue, places it in the parameter and returns true

bool Task::getCompleted(CustomerOrder& order)
{
	bool filled = false;
	if (!m_orders.empty() && m_orders.back().getOrderFillState())
	{
		order = std::move(m_orders.back());
		m_orders.pop_back();
		filled = true;
	}
	return filled;
}

// It writes the name of the Item this Task is responsible for into the parameter. 

void Task::validate(std::ostream& os)
{

	os << this->getName() << " --> ";
	if (m_pNextTask != nullptr) {
		os << m_pNextTask->getName();
	}
	else {
		os << "END OF LINE";
	}
	os << std::endl;
}

// It Moves the parameter onto the front of the CustomerOrder queue.

Task& Task::operator+=(CustomerOrder&& order)
{
	m_orders.push_front(std::move(order));
	return *this;
}
