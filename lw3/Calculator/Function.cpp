#include "Function.h"
#include <stdexcept>

// this не писать
Function::Function(ValueProvider* valueProvider)
	: 
	m_leftOperand(valueProvider)
{
	valueProvider->Subscribe(this);
	m_value = valueProvider->GetValue();
}

Function::Function(
	ValueProvider* left,
	Operation operation,
	ValueProvider* right
)
	: m_leftOperand(left),
	m_operation(operation),
	m_rightOperand(right)
{
	m_leftOperand->Subscribe(this);
	m_rightOperand->Subscribe(this);
	m_value = CalculateValue();
}

void Function::Update()
{
	m_value = CalculateValue();
	NotifyObservers();
}

double Function::CalculateValue() const
{
	double leftValue = m_leftOperand->GetValue();
	double rightValue = m_rightOperand->GetValue();

	switch (m_operation.value())
	{
	case Operation::Plus:
		return leftValue + rightValue;
	case Operation::Minus:
		return leftValue - rightValue;
	case Operation::Mult:
		return leftValue * rightValue;
	case Operation::Div:
		return leftValue / rightValue;
	}

	throw std::invalid_argument("Unknown operation");
}
