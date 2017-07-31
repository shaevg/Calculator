#include "expression.h"

#include <iostream>
#include <algorithm>
#include "core.h"
#include <functional>
//#include <regex>

using std::cout;
using std::endl;

Expression::Expression():_calculated(false) {}

int Expression::makeExpression(const string &expr)
{
	_expr = expr;

	if (parse()) {
		return 1;
	}

	if (calculate()) {
		return 1;
	}

	return 0;
}

int Expression::makeConstant(const string &expr)
{
	_expr = expr;

	// Проверка пустоты операнда
	if (_expr.empty()) {
		cout << "ERROR:  Operand is empty!" << endl;
		return 1;
	}

	// Проверка формата операнда
	{
		auto error = [&]() {
			std::cout << "ERROR: Operand \'" << _expr << "\' is incorrect!" << std::endl;
		};
		
		bool dot = false;
		int dotPos = 0;
		
		char c;
		for (int i = 0; i < _expr.length(); ++i) {
			c = _expr.at(i);
			if (!std::isdigit(c)) {
				if (!dot && c == '.') {
					dot = true;
					dotPos = i;
				} else {
					error();
					return 1;
				}
			}
		}
		
		int countInt = 0;
		int countDec = 0;
		
		if (dot) {
			countInt = dotPos;
			countDec = _expr.length() - dotPos - 1;
		} else {
			countInt = _expr.length();
		}
		
		if (countInt < 1 || countInt > 8) {
			error();
			return 1;
		}
		
		if (dot && (countDec > 2 || countDec == 0)) {
			error();
			return 1;
		}
		
		//std::regex reg("[0-9]{1,8}|[0-9]{1,8}[.][0-9]{1,2}");
		//if (!std::regex_match(_expr.c_str(), reg)) {
		//	cout << "ERROR: Operand \'" << _expr << "\' is incorrect!" << endl;
		//	return 1;
		//}
	}

	// Проверка выхода модуля числа за пределы 10 000 000
	{
		unsigned long module = std::stoul(_expr);
		if (module > 10000000) {
			cout << "ERROR: Value " << _expr << " is too large." << endl;
			return 1;
		}
	}

	_resultValue = Number(_expr);
	_calculated = true;
	return 0;
}

bool Expression::isCalculated()
{
	return _calculated;
}

Number Expression::getValue() const
{
	return _resultValue;
}

int Expression::parse()
{
	// Проверка пустоты строки выражения
	if (_expr.empty()) {
		cout<< "ERROR: Empty expression!" << endl;
		return 1;
	}

	// Если выражение начинается с '-', то добавить в начало '0'
	if (*_expr.begin() == '-') {
		_expr.insert(_expr.begin(),'0');
	}

	// Провека: нет ли по краям выражения операторов
	if (Core::isOperator(*_expr.begin()) ||
		Core::isOperator(*(_expr.end()-1)))
	{
		cout << "ERROR: An expression can't begin or end with such an operator." << endl;
		return 1;
	}

	//Разбор выражения
	{
		string substr;
		int flag;
		int pos = 0;
		int i = 0;

		//функция для добавления операнда
		auto addOperand = [&](const int& p, const int& count) {
			substr = _expr.substr(p, count);

			Expression expr;
			if (expr.makeConstant(substr)){
				return 1;
			}
			//_exprVector.push_back(std::move(expr));
			_exprVector.emplace_back(std::move(expr));
			return 0;
		};

		//функция для добавления выражения в круглых скобках
		auto addExpression = [&]() {
			++pos;
			flag = 1;
			++i;
			while (flag > 0) {
				if (_expr.at(i) == '(') {
					++flag;
				} else if (_expr.at(i) == ')') {
					--flag;
				}
				++i;
			}
			substr = _expr.substr(pos,i-pos-1);
			pos = i+1;

			Expression expr;
			if (expr.makeExpression(substr)){
				return 1;
			}
			//_exprVector.push_back(expr);
			_exprVector.emplace_back(std::move(expr));
			return 0;
		};

		//функция добавления оператора
		auto addOperator = [&]() {
			if (i < _expr.length()) {
				//_operatorVector.push_back(_expr.at(i));
				_operatorVector.emplace_back(_expr.at(i));
			}
		};

		//Разбор выражения
		while (i < _expr.length()) {

			if (Core::isOperator(_expr.at(i)))
			{
				if (addOperand(pos,i-pos)) {
					return 1;
				}
				addOperator();
				pos = i+1;
			}
			else if (_expr.at(i) == '(')
			{
				if (addExpression()) {
					return 1;
				}
				addOperator();
			}
			++i;
		}

		if (pos < _expr.length()) {
			if (addOperand(pos,_expr.length() - pos)) {
				return 1;
			}
		}
		_exprVector.shrink_to_fit();
	}

	return 0;
}

int Expression::calculate()
{
	if (_calculated) {
		return 0;
	}

	// Проверка: все ли операнды имеют вычисленное значение
	for(Expression& exp : _exprVector) {
		if (!exp.isCalculated()) {
			cout << "Error: calculation error." << endl;
			return 1;
		}
	}

	// Проверка: количесво операторов на 1 менше количества операндов
	if (_operatorVector.size() != _exprVector.size() - 1) {
		cout << "Error: incorrect expression \'" << _expr << "\'" << endl;
		return 1;
	}

	// Составление массива значений операндов
	for (const Expression& e : _exprVector) {
		//_resultVector.push_back(e.getValue());
		_resultVector.emplace_back(e.getValue());
	}

	_resultVector.shrink_to_fit();

	// Вычисление значения
	{
		int i = 0;
		char c;
		for(int priority = Core::getMaxPriority(); priority >= 0; --priority) {

			while (i < _operatorVector.size()) {
				c = _operatorVector.at(i);
				if (priority == Core::getPriority(c)) {

					Number result = Core::calculate(_resultVector.at(i),_resultVector.at(i+1),c);
					if (c == '/' && result.isInfinite()) {
						cout << "Error: division by zero." << endl;
						return 1;
					}
					auto it = _resultVector.begin();
					_resultVector.erase(it + i);
					_resultVector.erase(it + i);
					_resultVector.insert(it + i, result);
					_operatorVector.erase(_operatorVector.begin() + i);

				} else {
					++i;
				}
			}
			i = 0;
		}
	}

	if (_resultVector.size() != 1) {
		cout << "Error: calculation error." << endl;
		return 1;
	}
	
	_resultValue = *_resultVector.begin();
	_calculated = true;
	return 0;
}
