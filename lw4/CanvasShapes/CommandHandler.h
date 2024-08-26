#pragma once
#include <istream>
#include <functional>
#include <map>
#include "IShape.h"

class CommandHandler
{
public:
	CommandHandler(std::istream& input, std::ostream& output);
	void HandleCommand();
	void PrintResults();

private:
	void AddRectangle();
	void AddLine();
	void AddCircle();
	void AddTriangle();
	void PrintShape(IShape* const shape) const;
	IShape* GetShapeWithMaxArea() const;
	IShape* GetShapeWithMinPerimeter() const;

	using Handler = std::function<void()>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};