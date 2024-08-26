#include "Var.h"

Var::Var(double value)
{
	this->SetValue(value);
}

void Var::SetValue(double value)
{
	m_value = value;
	NotifyObservers();
}
