#include "CMyStringIterator.h"

//CMyStringIterator::CMyStringIterator(char* chars, CMyString* str)
//	: m_chars(chars), m_str(str)
//{
//}

//CMyStringIterator::CMyStringIterator(CMyString const& str)
//	: m_chars(str.m_chars)
//{
//}

char& CMyStringIterator::operator*()
{
	return *m_chars;
}

char& CMyStringIterator::operator[](size_t const& index) const
{
	return m_chars[index];
}

CMyStringIterator& CMyStringIterator::operator++()
{
	assert(m_chars != m_str->GetStringData() + m_str->GetLength());
	++m_chars;
	return *this;
}

CMyStringIterator CMyStringIterator::operator++(int)
{
	auto currentIter = *this;
	++(*this);
	return currentIter;
}

CMyStringIterator& CMyStringIterator::operator--()
{
	assert(m_chars != m_str->GetStringData());
	--m_chars;
	return *this;
}

CMyStringIterator CMyStringIterator::operator--(int)
{
	auto currentIter = *this;
	--(*this);
	return currentIter;
}

//CMyStringIterator CMyStringIterator::operator+(int value) const
//{
//	return CMyStringIterator(m_chars + value, m_str);
//}

//size_t CMyStringIterator::operator-(CMyStringIterator const& iter) const
//{
//	return m_chars - iter.m_chars;
//}
//
//CMyStringIterator operator+(int value, CMyStringIterator const& iter)
//{
//	return CMyStringIterator(iter.m_chars + value, iter.m_str);
//}
//
//CMyStringIterator::CMyStringIterator(char* chars)
//	: m_chars(chars)
//{
//}
