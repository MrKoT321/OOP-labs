#pragma once
#include "IPerson.h"

class IStudent : public IPerson
{
public:
	IStudent(
		std::string name,
		std::string surname,
		std::string middleName,
		std::string address,
		std::string school,
		std::string studyingClass
	) : IPerson(name, surname, middleName, address), m_school(school), m_studyingClass(studyingClass)
	{};

	std::string GetSchool() const { return m_school; }
	std::string GetStudyingClass() const { return m_studyingClass; }

private:
	std::string m_school;
	std::string m_studyingClass;
};