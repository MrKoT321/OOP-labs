#include "CRational.h"
#include <stdexcept>
#include <numeric>

CRational::CRational(int value)
	: m_numerator(value)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator), m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		throw std::invalid_argument("Denominator can't be equal to 0");
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator / m_denominator);
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int intPart = (int)ToDouble();
	CRational fracPart = *this - intPart;

	return std::pair<int, CRational>(intPart, fracPart);
}

CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(CRational const& rhs)
{
	return *this = *this + rhs;
}

CRational& CRational::operator-=(CRational const& rhs)
{
	return (*this += (-rhs));
}

CRational& CRational::operator*=(CRational const& rhs)
{
	return *this = *this * rhs;
}

CRational& CRational::operator/=(CRational const& rhs)
{
	return *this = *this / rhs;
}

std::strong_ordering CRational::operator<=>(CRational const& rhs) const
{
	int gcd1 = std::gcd(m_numerator, rhs.GetDenominator());
	int gcd2 = std::gcd(m_denominator, rhs.GetNumerator());
	int gcd = gcd1 * gcd2;
	return (m_numerator * rhs.GetDenominator() / gcd) <=> (rhs.GetNumerator() * m_denominator / gcd);
}

void CRational::Normalize()
{
	int gcd = std::gcd(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;

	if (m_denominator < 0)
	{
		m_denominator *= -1;
		m_numerator *= -1;
	}
}

CRational operator+(CRational const& lhs, CRational const& rhs)
{
	int commonDenominator = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
	int leftSummand = lhs.GetNumerator() * commonDenominator / lhs.GetDenominator();
	int rightSummand = rhs.GetNumerator() * commonDenominator / rhs.GetDenominator();
	return CRational(leftSummand + rightSummand, commonDenominator);
}

CRational operator-(CRational const& lhs, CRational const& rhs)
{
	return lhs + (-rhs);
}

CRational operator*(CRational const& lhs, CRational const& rhs)
{
	int gcd1 = std::gcd(lhs.GetDenominator(), rhs.GetNumerator());
	int gcd2 = std::gcd(lhs.GetNumerator(), rhs.GetDenominator());
	int gcd = gcd1 * gcd2;
	return CRational(lhs.GetNumerator() * rhs.GetNumerator() / gcd, 
		lhs.GetDenominator() * rhs.GetDenominator() / gcd);
}

CRational operator/(CRational const& lhs, CRational const& rhs)
{
	int gcd1 = std::gcd(lhs.GetDenominator(), rhs.GetDenominator());
	int gcd2 = std::gcd(lhs.GetNumerator(), rhs.GetNumerator());
	int gcd = gcd1 * gcd2;
	return CRational(lhs.GetNumerator() * (rhs.GetDenominator() / gcd),
		(lhs.GetDenominator() / gcd) * rhs.GetNumerator());
}

std::ostream& operator<<(std::ostream& stream, CRational const& r)
{
	stream << r.GetNumerator() << "/" << r.GetDenominator();

	return stream;
}

std::istream& operator>>(std::istream& stream, CRational& r)
{
	int numerator;
	int denominator;
	if (stream >> numerator && stream.get() == '/' && stream >> denominator)
	{
		r = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}
