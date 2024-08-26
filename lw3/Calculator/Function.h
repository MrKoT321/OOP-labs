#pragma once
#include "ValueProvider.h"
#include "IObserver.h"
#include "Operation.h"
#include <optional>

class Function:
	public ValueProvider,
	public IObserver
{
public:
	Function(ValueProvider* valueProvider);
	Function(
		ValueProvider* left,
		Operation operation,
		ValueProvider* right
	);
	void Update() override;
	
private:
	double CalculateValue() const;

	// можно заменить на обычные указатели
	ValueProvider* m_leftOperand;
	std::optional<Operation> m_operation;
	ValueProvider* m_rightOperand;
};