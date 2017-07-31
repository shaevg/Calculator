#include "calculator.h"

#include <iostream>
#include <algorithm>
//#include <regex>

using std::cout;
using std::endl;

Calculator::Calculator(const string &expression):
	_expressionStr(expression),
	_calculated(false)
{
}

Calculator::Calculator(const char *expression):
	_expressionStr(expression),
	_calculated(false)
{
}

bool Calculator::calculate()
{
	prepareExpression();

	if (!checkExpression()) {
		cout << "Calculation stopped." << endl;
		_calculated = false;
		return false;
	}

	if (_exprObj.makeExpression(_expr)) {
		_calculated = false;
		return  false;
	}

	_calculated = true;
	return true;
}

bool Calculator::isCalculated()
{
	return _calculated;
}

std::string Calculator::getResult()
{
	if (_calculated) {
		return _exprObj.getValue().toString();
	} else {
		return "no result";
	}
}

void Calculator::prepareExpression()
{
	cout << "Source expression: \'" << _expressionStr << "\'" << endl;
	//замена символов ',' на '.'
	_expr = _expressionStr;
	std::replace(_expr.begin(), _expr.end(), ',', '.');

	//удаление пробельных символов
	_expr.erase(std::remove_if(_expr.begin(), _expr.end(),[](char x){return std::isspace(x);}),
               _expr.end());
	
	cout << "Prepared expression: \'" << _expr << "\'" << endl;
}


bool Calculator::checkExpression()
{
	//проверка на корректность круглых скобок '(x+y' 'x+)5+6('
	{
		int flag = 0;
		int i = 0;
		while (flag >= 0 && i < _expr.length()) {
			if (_expr[i] == '(') {
				++flag;
			} else if (_expr[i] == ')') {
				--flag;
			}
			++i;
		}

		if (flag == 0 && i == _expr.length()) {
			//cout << "OK: Parentheses are set fine." << endl;
		} else {
			cout << "ERROR: Parentheses are set incorrectly!" << endl;
			return false;
		}
	}

	//поиск некорректно открытой или закрытой скобки скобки. 'x(y+z)' '(x*y)(z+k)'
	{
		char c;
		char p;
		
		auto error = [](const char& left, const char& right) {
			cout << "ERROR: Wrong parentheses! \'" << left << right << "\'" << endl;
		};
		
		for (int i = 0; i < _expr.length(); ++i) {
			c = _expr.at(i);		
			if (c == '(') {
				if (i > 0) {
					p = _expr.at(i-1);
					if (!(Core::isOperator(p) || p == '(')) {
						error(p,c);
						return false;
					}
				}
			} else if (c == ')') {
				if (i < _expr.length()-1){
					p = _expr.at(i+1);
					if (!(Core::isOperator(p) || p == ')')) {
						error(c,p);
						return false;
					}
				}
			}
		}
		
		//std::regex reg("[^-+*/(][(]|[)][^-+*/)]");
		/*
		std::cmatch result;
		if (std::regex_search(_expr.c_str(), result, reg)) {
			cout << "ERROR: Wrong parentheses!" << endl;
			for (int i = 0; i < result.size(); ++i){
				cout << result[i] << endl;
			}
			return false;
		} else {
			cout << "OK: Well open and close parentheses." << endl;
		}
		*/
	}
	return true;
}
