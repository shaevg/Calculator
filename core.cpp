#include "core.h"
#include <utility>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>

Core::OperatorsList Core::list = {'+','-','*','/'};
Core::OperatorPriorityList Core::priorityList = {0,0,1,1};

bool Core::isOperator(const char &c)
{
	for(const char& item : list) {
		if (c == item) {
			return true;
		}
	}
	return false;
}

int Core::getPriority(const char &c)
{
	for(int i = 0; i < list.size(); ++i) {
		if (list.at(i) == c) {
			return priorityList.at(i);
		}
	}
	return -1;
}

int Core::getMaxPriority()
{
	return *std::max_element(priorityList.begin(),priorityList.end());
}

Number Core::calculate(const Number &left, const Number &right, const char &operation)
{
	Number result;
	switch(operation) {
	case '+':{
		result = left + right;
		break;
	}
	case '-':{
		result = left - right;
		break;
	}
	case '*':{
		result = left * right;
		break;
	}
	case '/':{
		result = left / right;
		break;
	}
	};
	return result;
}

