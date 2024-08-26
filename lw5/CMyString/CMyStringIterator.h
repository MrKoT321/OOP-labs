#pragma once
#include "CMyString.h"
#include <iterator>
#include <cassert>

class CMyStringIterator
{
public:
	friend class CMyString;
	//CMyStringIterator(CMyString const& str);

	/*CMyStringIterator(char* chars, CMyString* str);
	CMyStringIterator(const char* chars, const CMyString* str);*/

	char& operator*();
	char& operator[](size_t const& index) const;
	CMyStringIterator& operator++();
	CMyStringIterator operator++(int);
	CMyStringIterator& operator--();
	CMyStringIterator operator--(int);
	friend CMyStringIterator operator+(int value, CMyStringIterator const& iter);
	//CMyStringIterator operator+(int value) const;
	//size_t operator-(CMyStringIterator const& iter) const;

private:
	//CMyStringIterator(char* chars);

	char* m_chars;
	CMyString* m_str;
};

CMyStringIterator operator+(int value, CMyStringIterator const& iter);