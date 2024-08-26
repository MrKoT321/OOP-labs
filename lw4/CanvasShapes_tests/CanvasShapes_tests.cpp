#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../CanvasShapes/CTriangle.h"
#include "../CanvasShapes/CCircle.h"
#include "../CanvasShapes/CLineSegment.h"
#include "../CanvasShapes/CRectangle.h"
#include "../CanvasShapes/CommandHandler.h"

void AssertShapeFields(
	IShape const& shape,
	double area,
	double perimeter,
	uint32_t outlineColor
)
{
	CHECK(std::round(shape.GetArea() * 100) / 100 == area);
	CHECK(std::round(shape.GetPerimeter() * 100) / 100 == perimeter);
	CHECK(shape.GetOutlineColor() == outlineColor);
}

void AssertSolidShape(
	ISolidShape const& solidShape,
	double area,
	double perimeter,
	uint32_t outlineColor,
	uint32_t fillColor
)
{
	CHECK(solidShape.GetFillColor() == fillColor);
	AssertShapeFields(solidShape, area, perimeter, outlineColor);
}

void AssertTriangleFields(
	CTriangle const& t,
	CPoint const& p1,
	CPoint const& p2,
	CPoint const& p3,
	double area,
	double perimeter,
	uint32_t fillColor,
	uint32_t outlineColor
)
{
	CHECK(t.GetVertex1() == p1);
	CHECK(t.GetVertex2() == p2);
	CHECK(t.GetVertex3() == p3);
	AssertSolidShape(t, area, perimeter, outlineColor, fillColor);
}

void AssertCircleFields(
	CCircle const& c,
	CPoint center,
	double radius,
	double area,
	double perimeter,
	uint32_t fillColor,
	uint32_t outlineColor
)
{
	CHECK(c.GetCenter() == center);
	CHECK(c.GetRadius() == radius);
	AssertSolidShape(c, area, perimeter, outlineColor, fillColor);
}

void AssertLineFields(
	CLineSegment const& line,
	CPoint start,
	CPoint end,
	double perimeter,
	uint32_t outlineColor
)
{
	CHECK(line.GetStartPoint() == start);
	CHECK(line.GetEndPoint() == end);
	AssertShapeFields(line, 0, perimeter, outlineColor);
}

void AssertRectangleFields(
	CRectangle const& rect,
	CPoint leftTop,
	CPoint rightBottom,
	double width,
	double height,
	double area,
	double perimeter,
	uint32_t fillColor,
	uint32_t outlineColor
)
{
	CHECK(rect.GetLeftTop() == leftTop);
	CHECK(rect.GetRightBottom() == rightBottom);
	CHECK(rect.GetWidth() == width);
	CHECK(rect.GetHeight() == height);
	AssertSolidShape(rect, area, perimeter, outlineColor, fillColor);
}

TEST_CASE("Create CTriangle")
{
	CPoint p1(1, 2);
	CPoint p2(2, 3);
	CPoint p3(4, 3);
	CTriangle triangle(p1, p2, p3, 111, 11);

	AssertTriangleFields(triangle, p1, p2, p3, 0.50, 6.58, 111, 11);
}


void CreateInvalidCCircle()
{
	CCircle circle(CPoint(5, 5), 0, 100, 100);
}

TEST_CASE("Create CCircle")
{
	CPoint p(10, 10);
	CCircle circle(p, 5, 100, 100);

	AssertCircleFields(circle, p, 5, 78.54, 31.42, 100, 100);

	CHECK_THROWS_AS(CCircle(CPoint(5, 5), 0, 100, 100), std::runtime_error);
	CHECK_THROWS_AS(CCircle(CPoint(5, 5), -1, 100, 100), std::runtime_error);
	
	CCircle circle1(CPoint(5, 5), 1, 200, 300);
	AssertCircleFields(circle1, CPoint(5, 5), 1, 3.14, 6.28, 200, 300);
}

TEST_CASE("Create CLineSegment")
{
	CPoint start(6, 8);
	CPoint end(6, 6);
	CLineSegment line(start, end, 919);

	AssertLineFields(line, start, end, 2, 919);
}

TEST_CASE("Create CRectangle")
{
	CRectangle rect(CPoint(2, 3), CPoint(1, 4), 2423, 12421);
	AssertRectangleFields(rect, CPoint(1, 3), CPoint(2, 4), 1, 1, 1, 4, 2423, 12421);

	CRectangle rect1(CPoint(1, 1), CPoint(3, 3), 555, 666);
	AssertRectangleFields(rect1, CPoint(1, 1), CPoint(3, 3), 2, 2, 4, 8, 555, 666);

	CRectangle rect2(CPoint(3, 3), CPoint(1, 1), 666, 555);
	AssertRectangleFields(rect2, CPoint(1, 1), CPoint(3, 3), 2, 2, 4, 8, 666, 555);

	CRectangle rect4(CPoint(1, 4), CPoint(2, 3), 2423, 12421);
	AssertRectangleFields(rect4, CPoint(1, 3), CPoint(2, 4), 1, 1, 1, 4, 2423, 12421);
}

TEST_CASE("Handle empty command")
{
	std::istringstream input;
	std::ostringstream output;
	CommandHandler handler(input, output);
	CHECK_THROWS_AS(handler.HandleCommand(), std::runtime_error);
	handler.PrintResults();
	CHECK(output.str() == "No shapes entered\n");
}

TEST_CASE("Handle circle declaration and print results")
{
	std::istringstream input("circle 5 6.5 10.2 000000 111111");
	std::ostringstream output;
	CommandHandler handler(input, output);
	CHECK_NOTHROW(handler.HandleCommand());
	handler.PrintResults();
	CHECK(output.str() == "Shape with max area:\ncircle 5 6.5 10.2 000000 111111\narea: 326.851\nperimeter: 64.0885\n\nShape with min perimeter:\ncircle 5 6.5 10.2 000000 111111\narea: 326.851\nperimeter: 64.0885\n");
}

TEST_CASE("Handle line declaration and print results")
{
	std::istringstream input("line 0.5 0.5 2 2.5 222222");
	std::ostringstream output;
	CommandHandler handler(input, output);
	CHECK_NOTHROW(handler.HandleCommand());
	handler.PrintResults();
	CHECK(output.str() == "Shape with max area:\nline 0.5 0.5 2 2.5 222222\narea: 0\nperimeter: 2.5\n\nShape with min perimeter:\nline 0.5 0.5 2 2.5 222222\narea: 0\nperimeter: 2.5\n");
}

TEST_CASE("Handle rectangle declaration and print results")
{
	std::istringstream input("rectangle 1 1 6.5 7.6 333333 444444");
	std::ostringstream output;
	CommandHandler handler(input, output);
	CHECK_NOTHROW(handler.HandleCommand());
	handler.PrintResults();
	CHECK(output.str() == "Shape with max area:\nrectangle 1 1 5.5 6.6 333333 444444\narea: 36.3\nperimeter: 24.2\n\nShape with min perimeter:\nrectangle 1 1 5.5 6.6 333333 444444\narea: 36.3\nperimeter: 24.2\n");
}

TEST_CASE("Handle triangle declaration and print results")
{
	std::istringstream input("triangle 1 1 6.5 7.6 9.000 8.1 333333 444444");
	std::ostringstream output;
	CommandHandler handler(input, output);
	CHECK_NOTHROW(handler.HandleCommand());
	handler.PrintResults();
	CHECK(output.str() == "Shape with max area:\ntriangle 1 1 6.5 7.6 9 8.1 333333 444444\narea: 6.125\nperimeter: 21.837\n\nShape with min perimeter:\ntriangle 1 1 6.5 7.6 9 8.1 333333 444444\narea: 6.125\nperimeter: 21.837\n");
}

TEST_CASE("Handle all figures and print results")
{
	std::string circleDeclaration = "circle 3 7 5.2 212121 111111 ";
	std::string lineDeclaration = "line 0.5 1 2 2 2f2f2f ";
	std::string rectangleDeclaration = "rectangle 1 1 6.5 10 121212 ffffff ";
	std::string triangleDeclaration = "triangle 1 10 6.4 7.8 3.001 9.9 aaaaaa aaaaaa";
	std::istringstream input(circleDeclaration + lineDeclaration + rectangleDeclaration + triangleDeclaration);
	std::ostringstream output;
	CommandHandler handler(input, output);

	CHECK_NOTHROW(handler.HandleCommand());
	CHECK_NOTHROW(handler.HandleCommand());
	CHECK_NOTHROW(handler.HandleCommand());
	CHECK_NOTHROW(handler.HandleCommand());
	handler.PrintResults();
	CHECK(output.str() == "Shape with max area:\ncircle 3 7 5.2 212121 111111\narea: 84.9487\nperimeter: 32.6726\n\nShape with min perimeter:\nline 0.5 1 2 2 2f2f2f\narea: 0\nperimeter: 1.80278\n");
}

TEST_CASE("Handle invalid color and print results")
{
	std::istringstream input("line 1.0 3 5 5 2f2f2");
	std::ostringstream output;
	CommandHandler handler(input, output);
	CHECK_NOTHROW(handler.HandleCommand());
	handler.PrintResults();
	CHECK(output.str() == "Shape with max area:\nline 1 3 5 5 02f2f2\narea: 0\nperimeter: 4.47214\n\nShape with min perimeter:\nline 1 3 5 5 02f2f2\narea: 0\nperimeter: 4.47214\n");
}