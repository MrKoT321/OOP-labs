#pragma once
#include "IStudent.h"

class IAdvancedStudent : public IStudent
{
public:
	IAdvancedStudent(
		std::string name,
		std::string surname,
		std::string middleName,
		std::string address,
		std::string school,
		std::string studyingClass,
		std::string dissertationTopic
	) : IStudent(name, surname, middleName, address, school, studyingClass), m_dissertationTopic(dissertationTopic)
	{};

	std::string GetDissertationTopic() const { return m_dissertationTopic; }

private:
	std::string m_dissertationTopic;
};