#pragma once
#include "CMyStringIterator.h"
#include <string>
#include <iostream>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);
	~CMyString();
	void Clear() noexcept;
	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	size_t GetCapacity() const;

	CMyString& operator=(CMyString const& rhs) noexcept;
	CMyString& operator=(CMyString&& rhs) noexcept;
	CMyString& operator+=(CMyString const& rhs);
	std::weak_ordering operator<=>(CMyString const& rhs) const noexcept;
	bool operator==(CMyString const& rhs) const noexcept;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

private:
	static inline const char EMPTY_CHAR = '\0';
	static inline char EMPTY_STRING[] = { EMPTY_CHAR };

	static char* Allocate(size_t size);

	char* m_chars;
	size_t m_length;
	size_t m_capacity;
};

CMyString operator+(CMyString const& lhs, CMyString const& rhs);
std::ostream& operator<<(std::ostream& stream, CMyString const& str);
std::istream& operator>>(std::istream& stream, CMyString& str);