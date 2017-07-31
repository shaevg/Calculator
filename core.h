#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include "expression.h"
#include "number.h"

#define OPERATOR_COUNT 4

class Core
{
public:
	Core() = delete;
	typedef std::array<char,OPERATOR_COUNT> OperatorsList;
	static OperatorsList list;

	typedef std::array<int,OPERATOR_COUNT> OperatorPriorityList;
	static OperatorPriorityList priorityList;

	static bool isOperator(const char& c);
	static int getPriority(const char& c);
	static int getMaxPriority();

	static Number calculate(const Number& left, const Number& right, const char& operation);
};

#undef OPERATOR_COUNT

#endif // CORE_H
