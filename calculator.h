#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "expression.h"

using std::string;

class Calculator
{
public:
	Calculator() = delete;
	Calculator(const string& expression);
	Calculator(const char* expression);
	bool calculate();
	bool isCalculated();
	std::string getResult();
private:
	string _expressionStr;
	string _expr;

	bool _calculated;

	Expression _exprObj;

	void prepareExpression();
	bool checkExpression();
};

#endif // CALCULATOR_H
