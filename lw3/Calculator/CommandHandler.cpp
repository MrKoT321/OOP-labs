#include "CommandHandler.h"
#include <sstream>
#include <regex>

CommandHandler::CommandHandler(Calculator& calc, std::istream& input, std::ostream& output)
	: m_calc(calc), m_input(input), m_output(output)
{
}

void CommandHandler::HandleCommand()
{
	std::string command;
	m_input >> command;

	auto action = m_actionsMap.find(command);
	if (action == m_actionsMap.end())
	{
		throw std::runtime_error("Using unknown command");
	}
	action->second();
}

void CommandHandler::ShowInfo()
{
	m_output 
		<< ":: var <identifier> -- Declares a variable of type double with the <identifier>" << std::endl
		<< ":: let <identifier>=<value> -- Assigns a numeric value to a variable with the <identifier>" << std::endl
		<< ":: let <identifier1>=<identifier2> -- Assigns the current value of a previously declared identifier named <identifier2> to a variable named <identifier1>" << std::endl
		<< ":: fn <identifier1>=<identifier2> -- Declares a new function with the previously undeclared name <identifier1>, whose value will be the value of identifier <identifier2>" << std::endl
		<< ":: fn <identifier1>=<identifier2><operation><identifier3> -- Declares a new function with the previously undeclared name <identifier1>, whose value will be the result of applying one of the following binary operations to the values of the previously declared identifiers <identifier2> and <identifier3>" << std::endl
		<< ":: print <identifier> -- Prints the value of a previously declared identifier to stdout" << std::endl
		<< ":: printvars -- Prints the names and values of all previously declared variables to stdout" << std::endl
		<< ":: printfns -- Prints the names and values of all previously declared functions to stdout" << std::endl
		;
}

void CommandHandler::PrintVars()
{
	m_output.setf(std::ios::fixed);
	m_output.precision(2);
	m_calc.EnumVars([this](const std::map<std::string, std::shared_ptr<Var>>& vars)
		{
			for (auto& [name, var]: vars)
			{
				m_output << name << ":" << var->GetValue() << std::endl;
			}
		}
	);
}

void CommandHandler::PrintFunctions()
{
	m_output.setf(std::ios::fixed);
	m_output.precision(2);
	m_calc.EnumFunctions([this](const std::map<std::string, std::shared_ptr<Function>>& functions)
		{
			for (auto& [name, function] : functions)
			m_output << name << ":" << function->GetValue() << std::endl;
		});
}

void CommandHandler::DefineVar()
{
	std::string name;
	m_input >> name;
	this->ValidateIdentifier(name);
	m_calc.DefineVar(name);
}

void CommandHandler::DefineFunction()
{
	std::string expression;
	m_input >> expression;
	std::string name;
	std::string leftOperand;
	std::optional<Operation> operation;
	std::string rightOperand;
	ParseFunctionExpression(expression, name, leftOperand, operation, rightOperand);
	ValidateIdentifier(name);

	if (!operation)
	{
		m_calc.DefineFunction(name, leftOperand);
	}
	else
	{
		m_calc.DefineFunction(name, leftOperand, operation.value(), rightOperand);
	}
}

void CommandHandler::LetVar()
{
	std::string expression;
	m_input >> expression;
	std::string leftOperand;
	std::string rightOperand;
	ParseVarExpression(expression, leftOperand, rightOperand);
	ValidateIdentifier(leftOperand);
	double value;
	
	if (IsIdentifierValid(rightOperand))
	{
		value = m_calc.GetValueByIdentifier(rightOperand);
	}
	else
	{
		value = round(stod(rightOperand) * 100) / 100;
	}
	m_calc.LetVar(leftOperand, value);
}

void CommandHandler::Print()
{
	std::string name;
	m_input >> name;
	m_output.setf(std::ios::fixed);
	m_output.precision(2);
	m_output << m_calc.GetValueByIdentifier(name) << std::endl;
}

void CommandHandler::ParseVarExpression(
	std::string const& exp,
	std::string& leftOperand,
	std::string& rightOperand
) const
{
	const std::regex reg(R"(([\w]+)=([\w.-]+))");
	std::smatch matchResult;

	if (!std::regex_match(exp, matchResult, reg))
	{
		throw std::runtime_error("Using invalid variable declaration");
	}

	leftOperand = matchResult[1];
	rightOperand = matchResult[2];
}

void CommandHandler::ParseFunctionExpression(
	std::string const& exp,
	std::string& name,
	std::string& leftOperand,
	std::optional<Operation>& operation,
	std::string& rightOperand
) const
{
	const std::regex reg(R"(([\w]+)=([\w]+)(([\+\-\*\/])([\w]+))?)");
	std::smatch matchResult;

	if (!std::regex_match(exp, matchResult, reg))
	{
		throw std::runtime_error("Using invalid function declaration");
	}

	name = matchResult[1];
	leftOperand = matchResult[2];
	operation = GetOperation(matchResult[4]);
	rightOperand = matchResult[5];
}

void CommandHandler::ValidateIdentifier(std::string const& name) const
{
	if (!IsIdentifierValid(name))
	{
		throw std::runtime_error("Invalid identifier");
	}
}

bool CommandHandler::IsIdentifierValid(std::string const& name) const
{
	if (std::isdigit(name[0]))
	{
		return false;
	}
	const std::regex reg(R"(\w+)");
	return std::regex_match(name, reg);
}

std::optional<Operation> CommandHandler::GetOperation(std::string const& str) const
{
	if (str.empty())
	{
		return std::nullopt;
	}
	switch (str[0])
	{
	case '+':
		return Operation::Plus;
	case '-':
		return Operation::Minus;
	case '*':
		return Operation::Mult;
	case '/':
		return Operation::Div;
	default:
		return std::nullopt;
	}
}
