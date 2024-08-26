#include "CMyString.h"
#include <memory>
#include <stdexcept>

CMyString::CMyString()
	: m_chars(Allocate(1)), m_length(0), m_capacity(0)
{
	m_chars[0] = EMPTY_CHAR;
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_chars(Allocate(length + 1)), m_length(length), m_capacity(length)
{
	std::copy(pString, pString + length, m_chars);
	m_chars[m_length] = EMPTY_CHAR;
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_chars, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	//: CMyString(other)
	: m_chars(other.m_chars), m_length(other.m_length), m_capacity(other.m_capacity)
{
	other.m_chars = EMPTY_STRING;
	other.m_length = 0;
	other.m_capacity = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	if (m_chars != EMPTY_STRING)
	{
		delete[] m_chars;
	}
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("Start index of substring can not be greater than string length");
	}

	return CMyString(m_chars + start, std::min(m_length - start, length));
}

void CMyString::Clear() noexcept
{
	if (m_chars != EMPTY_STRING)
	{
		m_length = 0;
		m_chars[0] = EMPTY_CHAR;
	}
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

CMyString& CMyString::operator=(CMyString const& rhs) noexcept
{
	if (&rhs != this)
	{
		if (m_capacity < rhs.m_length)
		{
			Allocate(rhs.m_capacity);
			m_capacity = rhs.m_capacity;
		}
		std::copy_n(rhs.m_chars, rhs.m_length + 1, m_chars);
		m_chars = rhs.m_chars;
		m_length = rhs.m_length;
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& rhs) noexcept
{
	if (&rhs != this)
	{
		if (m_chars != EMPTY_STRING)
		{
			delete[] m_chars;
		}
		m_chars = rhs.m_chars;
		m_length = rhs.m_length;
		m_capacity = rhs.m_capacity;

		m_chars = EMPTY_STRING;
		m_length = 0;
		rhs.m_capacity = 0;
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& rhs)
{
	auto commonLength = m_length + rhs.m_length;

	if (commonLength > m_capacity)
	{
		auto commonCapacity = std::max(rhs.m_capacity * 2, m_capacity * 2) + 1;
		auto result = Allocate(commonCapacity);
		std::copy_n(m_chars, m_length, result);
		std::copy_n(rhs.m_chars, rhs.m_length, result + m_length);
		result[commonLength] = EMPTY_CHAR;

		delete[] m_chars;
		m_chars = result;
		m_capacity = commonLength;
	}
	else
	{
		std::copy_n(rhs.m_chars, rhs.m_length, m_chars + m_length);
	}

	m_length = commonLength;

	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length || index < 0)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length || index < 0)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_chars[index];
}

std::weak_ordering CMyString::operator<=>(CMyString const& rhs) const noexcept
{
	return std::lexicographical_compare_three_way(
		m_chars, m_chars + m_length, rhs.m_chars, rhs.m_chars + rhs.m_length
	);
}

bool CMyString::operator==(CMyString const& rhs) const noexcept
{
	if (m_length != rhs.m_length)
	{
		return false;
	}

	return std::equal(m_chars, m_chars + m_length, rhs.m_chars);
}

char* CMyString::Allocate(size_t size)
{
	return new char[size];
}

CMyString operator+(CMyString const& lhs, CMyString const& rhs)
{
	if (lhs.GetLength() >= SIZE_MAX - rhs.GetLength())
	{
		throw std::length_error("Invalid string size");
	}

	CMyString newStr(lhs);
	newStr += rhs;

	return newStr;
}

std::ostream& operator<<(std::ostream& stream, CMyString const& str)
{
	stream << str.GetStringData();
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
	std::string chars;
	char ch;

	while (stream.get(ch) && chars.size() <= SIZE_MAX && ch != ' ')
	{
		chars += ch;
	}

	str = chars;

	return stream;
}
