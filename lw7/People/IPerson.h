#pragma once
#include <string>

class IPerson 
{
public:
    IPerson(std::string name, std::string surname, std::string middleName, std::string address)
        : m_name(name), m_surname(surname), m_middleName(middleName), m_address(address)
    {};

    std::string GetName() const { return m_name; }
    std::string GetSurname() const { return m_surname; }
    std::string GetMiddleName() const { return m_middleName; }
    std::string GetAddress() const { return m_address; }

private:
    std::string m_name;
    std::string m_surname;
    std::string m_middleName;
    std::string m_address;
};