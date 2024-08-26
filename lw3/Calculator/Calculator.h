#pragma once

#include "Function.h"
#include "Var.h"
#include <map>
#include <string>

class Calculator
{
public:
	// имя переменной + значение
	using CallbackVar = const std::function<void(const std::map<std::string, std::shared_ptr<Var>>)>&;
	using CallbackFunction = const std::function<void(const std::map<std::string, std::shared_ptr<Function>>)>&;

	void DefineVar(std::string const& name, double value = NAN);
	void LetVar(std::string const& name, double value);
	void DefineFunction(
		std::string const& name,
		std::string const& operandName
	);
	void DefineFunction(
		std::string const& name,
		std::string const& leftOperandName,
		Operation operation,
		std::string const& rightOperandName
	);
	double GetValueByIdentifier(std::string const& name) const;
	void EnumVars(CallbackVar callback) const;
	void EnumFunctions(CallbackFunction callback) const;
private:
	void VerifyUniqueIdentifier(std::string const& name) const;

	std::shared_ptr<Var> FindVar(std::string const& name) const;
	std::shared_ptr<Function> FindFunction(std::string const& name) const;
	std::shared_ptr<ValueProvider> FindValueProvider(std::string const& name) const;
	std::shared_ptr<ValueProvider> GetValueProvider(std::string const& name) const;

	//
	std::map<std::string, std::shared_ptr<Var>> m_vars{};
	std::map<std::string, std::shared_ptr<Function>> m_functions{};
};