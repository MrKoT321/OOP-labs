#include "CommandHandler.h"

#include "CRectangle.h"
#include "Common.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CCanvas.h"

CommandHandler::CommandHandler(std::istream& input, std::ostream& output)
	: m_input(input), m_output(output), m_actionMap({
			{ "rectangle", std::bind(&CommandHandler::AddRectangle, this) },
			{ "line", std::bind(&CommandHandler::AddLine, this) },
			{ "circle", std::bind(&CommandHandler::AddCircle, this) },
			{ "triangle", std::bind(&CommandHandler::AddTriangle, this) },
		})
{
}

void CommandHandler::HandleCommand()
{
	std::string command;
	m_input >> command;

	auto it = m_actionMap.find(command);
	if (it == m_actionMap.end())
	{
		throw std::runtime_error("Using unknown command");
	}
	it->second();
}

void CommandHandler::PrintResults()
{
	if (m_shapes.empty())
	{
		m_output << "No shapes entered" << std::endl;
		return;
	}
	m_output << "Shape with max area:" << std::endl;
	PrintShape(GetShapeWithMaxArea());
	m_output << std::endl << "Shape with min perimeter:" << std::endl;
	PrintShape(GetShapeWithMinPerimeter());
}

void CommandHandler::DrawShapes(sf::RenderWindow& window) const
{
	CCanvas canvas(window);
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CommandHandler::AddRectangle()
{
	double x1;
	double y1;
	double x2;
	double y2;
	std::string fillColorStr;
	std::string outlineColorStr;
	
	if (!(m_input >> x1 && m_input >> y1 && m_input >> x2 
		&& m_input >> y2 && m_input >> fillColorStr && m_input >> outlineColorStr))
	{
		throw std::runtime_error("Invalid rectangle declaration");
	}

	auto fillColor = GetUInt32ColorFromString(fillColorStr);
	auto outlineColor = GetUInt32ColorFromString(outlineColorStr);

	m_shapes.push_back(std::unique_ptr<IShape>(new CRectangle(CPoint(x1, y1), CPoint(x2, y2), fillColor, outlineColor)));
}

void CommandHandler::AddLine()
{
	double startX;
	double startY;
	double endX;
	double endY;
	std::string outlineColorStr;

	if (!(m_input >> startX && m_input >> startY && m_input >> endX && m_input >> endY && m_input >> outlineColorStr))
	{
		throw std::runtime_error("Invalid line declaration");
	}

	auto outlineColor = GetUInt32ColorFromString(outlineColorStr);

	m_shapes.push_back(std::unique_ptr<IShape>(new CLineSegment(CPoint(startX, startY), CPoint(endX, endY), outlineColor)));
}

void CommandHandler::AddCircle()
{
	double centerX;
	double centerY;
	double radius;
	std::string fillColorStr;
	std::string outlineColorStr;

	if (!(m_input >> centerX && m_input >> centerY && m_input >> radius 
		&& m_input >> fillColorStr && m_input >> outlineColorStr))
	{
		throw std::runtime_error("Invalid circle declaration");
	}

	auto fillColor = GetUInt32ColorFromString(fillColorStr);
	auto outlineColor = GetUInt32ColorFromString(outlineColorStr);

	m_shapes.push_back(std::unique_ptr<IShape>(new CCircle(CPoint(centerX, centerY), radius, fillColor, outlineColor)));
}

void CommandHandler::AddTriangle()
{
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	std::string fillColorStr;
	std::string outlineColorStr;

	if (!(m_input >> x1 && m_input >> y1 && m_input >> x2 && m_input >> y2 && m_input >> x3 && m_input >> y3
		&& m_input >> fillColorStr && m_input >> outlineColorStr))
	{
		throw std::runtime_error("Invalid circle declaration");
	}

	auto fillColor = GetUInt32ColorFromString(fillColorStr);
	auto outlineColor = GetUInt32ColorFromString(outlineColorStr);

	m_shapes.push_back(std::unique_ptr<IShape>(new CTriangle(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), fillColor, outlineColor)));
}

void CommandHandler::PrintShape(IShape* const shape) const
{
	m_output << shape->ToString() << std::endl;
	m_output << "area: " << shape->GetArea() << std::endl;
	m_output << "perimeter: " << shape->GetPerimeter() << std::endl;
}

IShape* CommandHandler::GetShapeWithMaxArea() const
{
	auto result = std::max_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b)
		{
			return a->GetArea() < b->GetArea();
		});

	return result->get();
}

IShape* CommandHandler::GetShapeWithMinPerimeter() const
{
	auto result = std::min_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b)
		{
			return a->GetPerimeter() < b->GetPerimeter();
		});

	return result->get();
}
