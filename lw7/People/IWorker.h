#pragma once
#include "IPerson.h"

class IWorker : public IPerson
{
public:
	IWorker(
		std::string name,
		std::string surname,
		std::string middleName,
		std::string address,
		std::string speciality
	) : IPerson(name, surname, middleName, address), m_speciality(speciality)
	{};

	std::string GetSpeciality() const { return m_speciality; }

private:
	std::string m_speciality;
};