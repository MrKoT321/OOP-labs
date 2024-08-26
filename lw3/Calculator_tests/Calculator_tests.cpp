#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Calculator/CommandHandler.h"
#include <math.h>

// Var
TEST_CASE("Create Var")
{
	Var var;
	CHECK(isnan(var.GetValue()));
	Var var1(2.11);
	CHECK(var1.GetValue() == 2.11);
}

TEST_CASE("Set value to Var")
{
	Var var;
	var.SetValue(2.22);
	CHECK(var.GetValue() == 2.22);
}

// Function
//TEST_CASE("Create Function")
//{
//	Var var(2.12);
//	Function f(std::make_shared<Var>(var));
//	CHECK(f.GetValue() == 2.12);
//
//	Var var1(3.12);
//	Function f1(std::make_shared<Var>(var), Operation::Plus, std::make_shared<Var>(var1));
//	CHECK(f1.GetValue() == 5.24);
//	Function f2(std::make_shared<Var>(var), Operation::Minus, std::make_shared<Var>(var1));
//	CHECK(f2.GetValue() == -1.00);
//	Function f3(std::make_shared<Var>(var), Operation::Mult, std::make_shared<Var>(1));
//	CHECK(f3.GetValue() == 2.12);
//	Function f4(std::make_shared<Var>(var), Operation::Div, std::make_shared<Var>(var));
//	CHECK(f4.GetValue() == 1.00);
//}

// Calculator
TEST_CASE("Define Var and Var with existed indifier in Calculator")
{
	Calculator calc;
	calc.DefineVar("x1", 123);
	CHECK(calc.GetValueByIdentifier("x1") == 123);

	CHECK_THROWS_AS(calc.DefineVar("x1", 212), std::runtime_error);
}

TEST_CASE("Let Var and Var with existed indifier in Calculator")
{
	Calculator calc;
	calc.LetVar("x1", 123);
	CHECK(calc.GetValueByIdentifier("x1") == 123);

	calc.LetVar("x1", 212);
	CHECK(calc.GetValueByIdentifier("x1") == 212);
}

TEST_CASE("Define Function and Function with existed indifier in Calculator")
{
	Calculator calc;
	calc.LetVar("x1", 123);
	calc.DefineFunction("f1", "x1");
	CHECK(calc.GetValueByIdentifier("f1") == calc.GetValueByIdentifier("x1"));

	calc.DefineVar("x2");
	calc.DefineFunction("f2", "x2");
	CHECK(isnan(calc.GetValueByIdentifier("f2")));

	calc.DefineFunction("f3", "x1", Operation::Plus, "x2");
	CHECK(isnan(calc.GetValueByIdentifier("f3")));

	CHECK_THROWS_AS(calc.DefineFunction("f2", "x1"), std::runtime_error);
	CHECK_THROWS_AS(calc.DefineFunction("f", "x"), std::runtime_error);
}

TEST_CASE("Define function and change Var value")
{
	Calculator calc;
	calc.LetVar("x1", 2.11);
	calc.LetVar("x2", 1.22);
	calc.DefineFunction("f1", "x1", Operation::Plus, "x2");
	CHECK(calc.GetValueByIdentifier("f1") == 3.33);

	calc.LetVar("x2", 3.22);
	CHECK(calc.GetValueByIdentifier("f1") == 5.33);
}

TEST_CASE("Enum Vars")
{
	Calculator calc;
	calc.LetVar("x1", 2.11);
	calc.LetVar("x2", 3.22);

	calc.EnumVars([](std::map<std::string, std::shared_ptr<Var>> const& vars)
		{
			CHECK(vars.size() == 2);
			CHECK(vars.contains("x1"));
			CHECK(vars.contains("x2"));
		}
	);
}

TEST_CASE("Enum Functions")
{
	Calculator calc;
	calc.LetVar("x1", 2.11);
	calc.LetVar("x2", 3.22);
	calc.DefineFunction("f1", "x2");
	calc.DefineFunction("f2", "x1", Operation::Plus, "x1");

	calc.EnumFunctions([](std::map<std::string, std::shared_ptr<Function>> const& functions)
		{
			CHECK(functions.size() == 2);
			CHECK(functions.contains("f1"));
			CHECK(functions.contains("f2"));
		}
	);
}

// CommandHandler
TEST_CASE("Handle command on empty string")
{
	Calculator calc;
	std::istringstream emptyInput;
	std::ostringstream output;
	CommandHandler commandHadler(calc, emptyInput, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Handle command on non existed command")
{
	Calculator calc;
	std::istringstream input("tetatet");
	std::ostringstream output;
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Define Vars from CommandHandler")
{
	Calculator calc;
	std::istringstream input("var x1 var x2");
	std::ostringstream output;
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(isnan(calc.GetValueByIdentifier("x1")));
	CHECK(isnan(calc.GetValueByIdentifier("x2")));
}

TEST_CASE("Set value on Var's define")
{
	Calculator calc;
	std::istringstream input("var x1=100 var x2");
	std::ostringstream output;
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}


TEST_CASE("Define Vars with same identifier")
{
	Calculator calc;
	std::istringstream inputWithDefineSameValues("var x1 var x1");
	std::ostringstream output;
	CommandHandler commandHadler(calc, inputWithDefineSameValues, output);
	
	commandHadler.HandleCommand();
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
	CHECK(isnan(calc.GetValueByIdentifier("x1")));
}

TEST_CASE("Define Var on invalid command")
{
	Calculator calc;
	std::istringstream input("var");
	std::ostringstream output;
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Define Function from CommandHandler")
{
	Calculator calc;
	std::istringstream input("var x fn f=x");
	std::ostringstream output;
	CommandHandler commandHadler(calc, input, output);
	
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(isnan(calc.GetValueByIdentifier("x")));
	CHECK(isnan(calc.GetValueByIdentifier("f")));
}

TEST_CASE("Define Functions with same identifier")
{
	Calculator calc;
	std::istringstream input("var x1 var x2 fn f=x1 fn f=x2");
	std::ostringstream output;
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Define Function on non existed identifier")
{
	Calculator calc;
	std::istringstream input("fn f=x2");
	std::ostringstream output;
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Define Function on invalid command")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("fn f= fn f");
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Define Function with Operator")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("var x fn f1=x+x fn f2=x-x fn f3=x*x fn f4=x/x");
	CommandHandler commandHadler(calc, input, output);
	
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(isnan(calc.GetValueByIdentifier("x")));
	CHECK(isnan(calc.GetValueByIdentifier("f1")));
	CHECK(isnan(calc.GetValueByIdentifier("f2")));
	CHECK(isnan(calc.GetValueByIdentifier("f3")));
	CHECK(isnan(calc.GetValueByIdentifier("f4")));
}

TEST_CASE("Define Function with non existed Operator")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("var x fn f1=x^x");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Define Function without second operand")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("var x fn f1=x+");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Let Var with CommandHandler")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=1.111");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("x") == 1.11);
}

TEST_CASE("Let Var equal to another Var")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=1.111 let y=x");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("x") == calc.GetValueByIdentifier("y"));
}

TEST_CASE("Let Var equal to Function result")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=1.111 fn f=x let y=f");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("x") == calc.GetValueByIdentifier("f"));
	CHECK(calc.GetValueByIdentifier("f") == calc.GetValueByIdentifier("y"));
}

TEST_CASE("Let Var equal to non existed operand")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=y");
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Let Var with on invalid command")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x let x=");
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Print Var with default value")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("var x print x");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(output.str() == "nan\n");
}

TEST_CASE("Print Var with value")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=1.115 print x");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(output.str() == "1.12\n");
}

TEST_CASE("Print Function result")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=1.115 fn f=x+x print f");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(output.str() == "2.24\n");
}

TEST_CASE("Print invalid identifier")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("print f");
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Print Vars")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 var y fn f=x-y printvars");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(output.str() == "x:100.00\ny:nan\n");
}

TEST_CASE("Print Vars without declaration")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("printvars");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	CHECK(output.str().empty());
}

TEST_CASE("Print Functions")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 var y let z=11.115 fn f=x-y fn sum=x+z printfns");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(output.str() == "f:nan\nsum:111.12\n");
}

TEST_CASE("Print Functions without delared Functions")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 var y let z=11.115 printfns");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(output.str().empty());
}

TEST_CASE("Change value after declared in Function")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 let y=200 fn f=y*x let y=0");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("f") == 20000.00);
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("f") == 0.00);
}

TEST_CASE("Change value after declared in Var")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 let y=x let x=10");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("y") == 100.00);
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("y") == 100.00);
}

TEST_CASE("Change value in function after declared Var as Function value")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 let y=10 fn f=x+y let z=f let y=100");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("z") == 110.00);
	commandHadler.HandleCommand();
	CHECK(calc.GetValueByIdentifier("z") == 110.00);
}

TEST_CASE("Create Var with invalid identifier")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let 1x=100 var 1x");
	CommandHandler commandHadler(calc, input, output);

	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Create Function with invalid identifier")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 fn 2f=x");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	CHECK_THROWS_AS(commandHadler.HandleCommand(), std::runtime_error);
}

TEST_CASE("Create Functions with diffrent registers")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("let x=100 fn f=x fn F=x+x");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	commandHadler.HandleCommand();
	CHECK_NOTHROW(commandHadler.HandleCommand());
}

TEST_CASE("Create Vars with diffrent registers")
{
	Calculator calc;
	std::ostringstream output;
	std::istringstream input("var XO var xo let Xo=100 let xO=1.111");
	CommandHandler commandHadler(calc, input, output);

	commandHadler.HandleCommand();
	CHECK_NOTHROW(commandHadler.HandleCommand());
	CHECK_NOTHROW(commandHadler.HandleCommand());
	CHECK_NOTHROW(commandHadler.HandleCommand());
}



TEST_CASE("Test 1000000 functions")
{
	Calculator calc;
	std::ostringstream output;
	std::string inputStr = "let x1=0 let x2=1 ";
	for (int i = 3; i <= 51; ++i)
	{
		std::string str = "fn x" + std::to_string(i) + "=x" + std::to_string(i - 1) + "+x" + std::to_string(i - 2) + " ";
		inputStr += str;
	}
	std::istringstream input(inputStr);
	CommandHandler commandHadler(calc, input, output);

	for (int i = 0; i < 51; ++i)
	{
		commandHadler.HandleCommand();
	}
	CHECK(calc.GetValueByIdentifier("x51") == 12586269025.00);
}

//	> let v0 = 0
//> let v1 = 1
//> fn f0 = f0
//Var or Function with same indefier is not existed
//> fn f0 = v0
//> fn f1 = f1
//Var or Function with same indefier is not existed
//> fn f1 = v1
//> fn f2 = f1 + f0
//> fn f3 = f2 + f1
//> fn f4 = f3 + f2
//> fn f5 = f4 + f3
//> print f5
//5.00
//> let v0 = 1