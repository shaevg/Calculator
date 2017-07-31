
#include "CalculatorTestClass.h"
#include "../calculator.h"


CPPUNIT_TEST_SUITE_REGISTRATION(CalculatorTestClass);

CalculatorTestClass::CalculatorTestClass()
{
}

CalculatorTestClass::~CalculatorTestClass()
{
}

void CalculatorTestClass::setUp()
{
}

void CalculatorTestClass::tearDown()
{
}

void CalculatorTestClass::testCheckExpression()
{
	
	// тесты из задания
	{
		Calculator calc = "-1 + 5 - 3";
		if (!(calc.calculate() && calc.getResult() == "1")) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
		if (!(calc.calculate() && calc.getResult() == "11")) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "-10 + (8 * 2.5) - (3 / 1,5)";
		if (!(calc.calculate() && calc.getResult() == "8")) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	
	{
		Calculator calc = "1.1 + 2.1 + abc";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	// тесты на неправильные скобки
	{
		Calculator calc = "(5+5)(5+5)";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "((5+5)*(5+5)";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "(5+5)*(5+5))";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "(5+)5)*(5+5)";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	// тесты на операторы рядом со скобками
	{
		Calculator calc = "(5 + 5) * (5 + 5).";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "(5 + 5) * (5 + 5) - ()";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "11 (5 + 5)*(5 + 5)";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "11. (5 + 5)*(5 + 5)";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "(5 + 5) * (5 + 5) 12";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "(5 + 5)*(5 + 5) .12";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	// произвольные тесты
	{
		Calculator calc = "-(10+2*5)/(5+5*3)";
		if (!(calc.calculate() && calc.getResult() == "-1")) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "(-)*(5+5).";
		if (calc.calculate()) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Calculator calc = "((((-((((((1.23))))))))))+(((((((-(((((5.43))))))))))))";
		if (!(calc.calculate() && calc.getResult() == "-6.66")) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	CPPUNIT_ASSERT(true);
}

