#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include "core.h"
#include "number.h"

using std::string;
using std::vector;

class Expression
{

public:

	Expression();
	int makeExpression(const string& expr);
	int makeConstant(const string& expr);
	bool isCalculated();
	Number getValue() const;
private:

	int parse();
	int calculate();

	Number _resultValue;
	bool _calculated;

	string _expr;
	vector<Expression> _exprVector;
	vector<Number> _resultVector;
	vector<char> _operatorVector;
};

#endif // EXPRESSION_H
