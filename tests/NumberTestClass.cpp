
#include "NumberTestClass.h"
#include "../number.h"
#include <cmath>

CPPUNIT_TEST_SUITE_REGISTRATION(NumberTestClass);

NumberTestClass::NumberTestClass()
{
}

NumberTestClass::~NumberTestClass()
{
}

void NumberTestClass::setUp()
{
}

void NumberTestClass::tearDown()
{
}

void NumberTestClass::testOperatorPlus()
{
	//малые целые числа
	for (int x = -10; x <= 10; ++x) {
		for (int y = -10; y <= 10; ++y) {
			Number xNum(x);
			Number yNum(y);
			
			if ((xNum + yNum) != Number(x + y)) {
				CPPUNIT_ASSERT(false);
			}
		}
	}
	
	//большие целые с малыми целыми
	{
		int mod = 9999990;
		for (int x = -10; x <= 10; ++x) {
			for (int y = -10; y <= 10; ++y) {
				Number xNum(mod + x);
				Number yNum(y);
				if ((xNum + yNum) != Number((mod + x) + y)) {
					CPPUNIT_ASSERT(false);
				}
			}
		}
	}
	
	{
		int mod = -9999990;
		for (int x = -10; x <= 10; ++x) {
			for (int y = -10; y <= 10; ++y) {
				Number xNum(mod + x);
				Number yNum(y);
				
				if ((xNum + yNum) != Number((mod + x) + y)) {
					CPPUNIT_ASSERT(false);
				}
			}
		}
	}
	
	//Десятичные малые
	{
		for (double y = -1; y <= 1; y += 0.01) {
			for (double x = -1; x <= 1; x += 0.01) {
				std::ostringstream streamX;
				streamX << std::round(x*100)/100;
				std::string xStr = streamX.str();
				
				std::ostringstream streamY;
				streamY << std::round(y*100)/100;
				std::string yStr = streamY.str();
				
				std::ostringstream streamZ;
				streamZ << std::round((x+y)*100)/100;
				std::string zStr = streamZ.str();
				
				Number xNum = xStr;
				Number yNum = yStr;
				Number zNum = xNum + yNum;
				
				std::string res = zNum.toString();
				
				if (res != zStr) {
					CPPUNIT_ASSERT(false);
				}
			}
		}
	}
	
	{
		Number x ("5123456.78");
		Number y ("4654321.96");
		Number z = x + y;
		if (z.toString() != "9777778.74") {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Number x ("9123456.86");
		Number y ("-9654321.97");
		Number z = x + y;
		//std::string zStr = z.toString();
		if (z.toString() != "-530865.11") {
			CPPUNIT_ASSERT(false);
		}
	}
	
	
	CPPUNIT_ASSERT(true);
}

void NumberTestClass::testOperatorMinus()
{
	//малые целые числа
	for (int x = -10; x <= 10; ++x) {
		for (int y = -10; y <= 10; ++y) {
			Number xNum(x);
			Number yNum(y);
			
			if ((xNum - yNum) != Number(x - y)) {
				CPPUNIT_ASSERT(false);
			}
		}
	}
	
	//большие целые с малыми целыми
	{
		int mod = 9999990;
		for (int x = -10; x <= 10; ++x) {
			for (int y = -10; y <= 10; ++y) {
				Number xNum(mod + x);
				Number yNum(y);
				if ((xNum - yNum) != Number((mod + x) - y)) {
					CPPUNIT_ASSERT(false);
				}
			}
		}
	}
	
	{
		int mod = -9999990;
		for (int x = -10; x <= 10; ++x) {
			for (int y = -10; y <= 10; ++y) {
				Number xNum(mod + x);
				Number yNum(y);
				
				if ((xNum - yNum) != Number((mod + x) - y)) {
					CPPUNIT_ASSERT(false);
				}
			}
		}
	}
	
	//Десятичные малые
	{
		for (double y = -1; y <= 1; y += 0.01) {
			for (double x = -1; x <= 1; x += 0.01) {
				std::ostringstream streamX;
				streamX << std::round(x*100)/100;
				std::string xStr = streamX.str();
				
				std::ostringstream streamY;
				streamY << std::round(y*100)/100;
				std::string yStr = streamY.str();
				
				std::ostringstream streamZ;
				streamZ << std::round((x - y)*100)/100;
				std::string zStr = streamZ.str();
				
				Number xNum = xStr;
				Number yNum = yStr;
				Number zNum = xNum - yNum;
				
				std::string res = zNum.toString();
				
				if (res != zStr) {
					CPPUNIT_ASSERT(false);
				}
			}
		}
	}
	
	{
		Number x ("9000000.02");
		Number y ("8999900.07");
		Number z = x - y;
		if (z.toString() != "99.95") {
			CPPUNIT_ASSERT(false);
		}
	}
	
	{
		Number x ("5123456.86");
		Number y ("-4123456.97");
		Number z = x - y;
		if (z.toString() != "9246913.83") {
			CPPUNIT_ASSERT(false);
		}
	}
	
	CPPUNIT_ASSERT(true);
}

void NumberTestClass::testOperatorMultiply()
{
	//умножение на ноль
	{
		Number x("-9123456.98");
		Number y(0);
		if ((x*y) != Number(0) || (y*x) != Number(0)) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	for (int x = -10; x <= 10; ++x) {
		for (int y = -10; y <= 10; ++y) {
			Number xNum(x);
			Number yNum(y);
			
			if ((xNum * yNum) != Number(x * y)) {
				CPPUNIT_ASSERT(false);
			}
		}
	}
	
	//умножение произвольных чисел
	{
		Number x("-8436.98");
		Number y("1984.17");
		Number z = x * y;
		if (z.toString() != "-16740402.61") {
			CPPUNIT_ASSERT(false);
		}
	}
	
	CPPUNIT_ASSERT(true);
}

void NumberTestClass::testOperatorDivide()
{
	//деление нуля
	{
		Number x(0);
		Number y("-9123456.98");
		Number z = x / y;
		if (z != Number(0)) {
			CPPUNIT_ASSERT(false);
		}
	}
	
	// малые целые числа
	for (int x = -10; x <= 10; ++x) {
		for (int y = -10; y <= 10; ++y) {
			
			if (y == 0 || x == 0) {
				break;
			}
			
			Number xNum(x);
			Number yNum(y);
			Number zNum = xNum / yNum;
			std::string result = zNum.toString();
			
			double z = ((double)x)/y;
			std::ostringstream streamZ;
			streamZ << std::round(z*100)/100;
			std::string zStr = streamZ.str();
			
			if (result != zStr) {
				CPPUNIT_ASSERT(false);
			}
		}
	}
	
	CPPUNIT_ASSERT(true);
}
