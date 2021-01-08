// Name: Parsa Jalilifar
// Seneca Student ID: 133308189
// Seneca email: pjalilifar@myseneca.ca
// Date of completion:
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include <fstream>
#include "LineManager.h"

LineManager::LineManager(const std::string& fileName, std::vector<Task*>& line, std::vector<CustomerOrder>& order)
{
	ToBeFilled.resize(order.size());
	AssemblyLine.resize(line.size());
	std::move(order.begin(), order.end(), ToBeFilled.begin());
	std::move(line.begin(), line.end(), AssemblyLine.begin());
	m_cntCustomerOrder = order.size();

	std::ifstream file(fileName);

	if (!file)
	{
		throw  "ERROR: Cannot open file [" + fileName + "].";
	}

	while (!file.eof())
	{
		std::string record;
		std::getline(file, record);

		Utilities util;
		bool ok = true;
		size_t pos = 0;

		if (record.find(util.getDelimiter()) != std::string::npos)
		{
			std::string token = util.extractToken(record, pos, ok);
			std::string taskToken = util.extractToken(record, pos, ok);

			for (size_t i = 0; i < AssemblyLine.size(); i++)
			{
				if (AssemblyLine[i]->getName() == token)
				{
					for (size_t j = 0; j < AssemblyLine.size(); j++)
					{
						if (AssemblyLine[j]->getName() == taskToken)
						{
							AssemblyLine[i]->setNextTask(*AssemblyLine[j]);
						}
					}
				}
			}
		}

	}

	file.close();
}

bool LineManager::run(std::ostream& os)
{
	bool status = true;
	static size_t orderCCounter = 0;

	if (orderCCounter < m_cntCustomerOrder)
	{
		if (!ToBeFilled.empty())
		{
			AssemblyLine.back()->operator+=(std::move(ToBeFilled.front()));
			ToBeFilled.pop_front();
			Completed.resize(Completed.size() + 1);
		}

		for (size_t i = 0; i < AssemblyLine.size(); i++)
		{
			AssemblyLine[i]->runProcess(os);
		}

		for (int j = AssemblyLine.size() - 1; j >= 0; j--)
		{
			if (orderCCounter < Completed.size())
			{
				if (AssemblyLine[j]->getCompleted(Completed[orderCCounter]))
				{
					orderCCounter++;
				}
			}
		}

		for (size_t j = 0; j < AssemblyLine.size(); j++)
		{
			AssemblyLine[j]->moveTask();
		}

		status = false;
	}

	return status;
}

void LineManager::displayCompleted(std::ostream& os) const
{
	for (size_t i = 0; i < Completed.size(); i++)
		Completed[i].display(os);

}

void LineManager::validateTasks() const
{
	for (size_t i = 0; i < AssemblyLine.size(); i++)
		AssemblyLine[i]->validate(std::cout);
}
