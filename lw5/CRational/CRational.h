#pragma once
#include <iostream>

class CRational
{
public:
	CRational() = default;
	CRational(int value);
	CRational(int numerator, int denominator);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble()const;
	std::pair<int, CRational> ToCompoundFraction() const;
	
	CRational operator+() const;
	CRational operator-() const;
	CRational& operator+=(CRational const& rhs);
	CRational& operator-=(CRational const& rhs);
	CRational& operator*=(CRational const& rhs);
	CRational& operator/=(CRational const& rhs);
	std::strong_ordering operator<=>(CRational const& rhs) const;
	bool operator==(CRational const& rhs) const = default;

private:
	void Normalize();

	int m_numerator = 0;
	int m_denominator = 1;
};

CRational operator+(CRational const& lhs, CRational const& rhs);
CRational operator-(CRational const& lhs, CRational const& rhs);
CRational operator*(CRational const& lhs, CRational const& rhs);
CRational operator/(CRational const& lhs, CRational const& rhs);
std::ostream& operator<<(std::ostream& stream, CRational const& r);
std::istream& operator>>(std::istream& stream, CRational const& r);