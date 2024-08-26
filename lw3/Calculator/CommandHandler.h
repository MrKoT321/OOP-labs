#pragma once
#include "Calculator.h"

class CommandHandler
{
public:
	CommandHandler(Calculator& calc, std::istream& input, std::ostream& output);
	void HandleCommand();
private:
	void ShowInfo();
	void PrintVars();
	void PrintFunctions();
	void DefineVar();
	void DefineFunction();
	void LetVar();
	void Print();
	void ParseVarExpression(std::string const& exp, std::string& leftOperand, std::string& rightOperand) const;
	void ParseFunctionExpression(
		std::string const& exp,
		std::string& name,
		std::string& leftOperand,
		std::optional<Operation>& operation,
		std::string& rightOperand
	) const;
	void ValidateIdentifier(std::string const& name) const;
	bool IsIdentifierValid(std::string const& name) const;
	std::optional<Operation> GetOperation(std::string const& str) const;

	Calculator& m_calc;
	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<void()>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionsMap = {
		{ "info", std::bind(&CommandHandler::ShowInfo, this) },
		{ "printvars", std::bind(&CommandHandler::PrintVars, this) },
		{ "var", std::bind(&CommandHandler::DefineVar, this) },
		{ "let", std::bind(&CommandHandler::LetVar, this) },
		{ "printfns", std::bind(&CommandHandler::PrintFunctions, this)},
		{ "fn", std::bind(&CommandHandler::DefineFunction, this)},
		{ "print", std::bind(&CommandHandler::Print, this)},
	};
};