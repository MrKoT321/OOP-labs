#pragma once
#include "IPerson.h"

class ITeacher : public IPerson
{
public:
	ITeacher(
		std::string name,
		std::string surname,
		std::string middleName,
		std::string address,
		std::string subject
	) : IPerson(name, surname, middleName, address), m_subject(subject)
	{};

	std::string GetSubject() const { return m_subject; }

private:
	std::string m_subject;
};