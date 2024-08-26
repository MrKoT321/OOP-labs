#include "Calculator.h"
#include <stdexcept>

void Calculator::DefineVar(std::string const& name, double value)
{
	VerifyUniqueIdentifier(name);
	
	auto var = std::make_shared<Var>(value);
	m_vars.emplace(name, var);
}

void Calculator::LetVar(std::string const& name, double value)
{
	auto var = FindVar(name);
	if (var == nullptr)
	{
		DefineVar(name, value);
		return;
	}
	var->SetValue(value);
}

void Calculator::DefineFunction(std::string const& name, std::string const& operandName)
{
	VerifyUniqueIdentifier(name);

	auto valueProvider = GetValueProvider(operandName);
	auto function = Function(valueProvider.get());
	m_functions.emplace(name, function);
}

void Calculator::DefineFunction(
	std::string const& name,
	std::string const& leftOperandName,
	Operation operation,
	std::string const& rightOperandName
)
{
	VerifyUniqueIdentifier(name);
	
	auto leftValueProvider = GetValueProvider(leftOperandName);
	auto rightValueProvider = GetValueProvider(rightOperandName);
	auto function = Function(leftValueProvider.get(), operation, rightValueProvider.get());
	//auto function = std::make_shared<Function>(leftValueProvider, operation, rightValueProvider);
	m_functions.emplace(name, function);
}

double Calculator::GetValueByIdentifier(std::string const& name) const
{
	return GetValueProvider(name)->GetValue();
}

void Calculator::EnumVars(CallbackVar callback) const
{
	callback(m_vars);
}

void Calculator::EnumFunctions(CallbackFunction callback) const
{
	callback(m_functions);
}

void Calculator::VerifyUniqueIdentifier(std::string const& name) const
{
	if (m_functions.contains(name) || m_vars.contains(name))
	{
		throw std::runtime_error("Identifier is already in use");
	}
}

std::shared_ptr<Var> Calculator::FindVar(std::string const& name) const
{
	auto var = m_vars.find(name);
	return var != m_vars.end() ? var->second : nullptr;
}

std::shared_ptr<Function> Calculator::FindFunction(std::string const& name) const
{
	auto function = m_functions.find(name);
	return function != m_functions.end() ? function->second : nullptr;
}

std::shared_ptr<ValueProvider> Calculator::FindValueProvider(std::string const& name) const
{
	std::shared_ptr<ValueProvider> valueProvider = FindVar(name);
	if (valueProvider != nullptr)
	{
		return valueProvider;
	}

	valueProvider = FindFunction(name);
	if (valueProvider != nullptr)
	{
		return valueProvider;
	}

	return nullptr;
}

std::shared_ptr<ValueProvider> Calculator::GetValueProvider(std::string const& name) const
{
	auto valueProvider = FindValueProvider(name);
	if (valueProvider == nullptr)
	{
		throw std::runtime_error("Var or Function with same indefier is not existed");
	}

	return valueProvider;
}

