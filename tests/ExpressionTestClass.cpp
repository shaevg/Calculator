/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ExpressionTestClass.cpp
 * Author: user
 *
 * Created on 31.07.2017, 20:05:06
 */

#include "ExpressionTestClass.h"
#include "../expression.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ExpressionTestClass);

ExpressionTestClass::ExpressionTestClass()
{
}

ExpressionTestClass::~ExpressionTestClass()
{
}

void ExpressionTestClass::setUp()
{
}

void ExpressionTestClass::tearDown()
{
}

void ExpressionTestClass::testMakeConstant()
{
	{
		Expression exp;
		if (!exp.makeConstant("123.")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant("123.1a")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant("123.a3")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant(".01")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant("+")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant("12.43.1")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant("123456789.12")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant("123.123")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (!exp.makeConstant("12345678.12")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	{
		Expression exp;
		if (exp.makeConstant("10000000.00")) {
			CPPUNIT_ASSERT(false);
		}	
	}
	
	CPPUNIT_ASSERT(true);
}


