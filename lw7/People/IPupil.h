#pragma once
#include "IPerson.h"

class IPupil : public IPerson
{
	IPupil(std::string name, std::string surname, std::string middleName, std::string address)
		: IPerson(name, surname, middleName, address) 
	{};
};