#include "number.h"
#include <utility>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>

Number::Number()
{
	_sign = 1;
	_int = 0;
	_dec = 0;
}

Number::Number(const Number &num)
{
	_sign = num._sign;
	_int = num._int;
	_dec = num._dec;
}

Number::Number(std::string num)
{
	_sign = 1;
	_int = 0;
	_dec = 0;

	if (!num.empty()) {
		if (*num.begin() == '-'){
			_sign = -1;
			num.erase(num.begin(),num.begin()+1);
		}
		char c = *num.begin();
		int i = 0;
		while(i < num.length() && c != '.') {
			c = num.at(i);
			++i;
		}

		_int = std::stoi(num.substr(0,i));

		if (i < num.length()) {
			_dec = std::stod("0." + num.substr(i,num.length()));
		}
	}
}

Number::Number(const double &num)
{
	_sign = (num >= 0) - (num < 0);
	_int = _sign*static_cast<int64_t>(num);
	_dec = _sign*static_cast<long double>(num) - _int;
}

Number::Number(const int &num)
{
	_sign = (num >= 0) - (num < 0);
	_int = _sign*static_cast<int64_t>(num);
	_dec = 0;
}

std::string Number::toString() const
{
	std::ostringstream out;
	if (_sign == -1 && (_int != 0 || _dec != 0)) {
		out << '-';
	}
	out << _int;
	if (_dec != 0) {
		std::ostringstream stream;
		stream << std::round(_dec*100)/100;
		std::string str = stream.str();
		str.erase(str.begin(), str.begin()+1);
		out << str;
	}
	std::string str = out.str();
	return str;
}

bool Number::isInfinite()
{
	if (_sign == -1 && _int == 0 && _dec == 0) {
		return true;
	}
	return false;
}

Number &Number::operator=(const Number &num)
{
	_sign = num._sign;
	_int = num._int;
	_dec = num._dec;
	return *this;
}

Number Number::abs() const
{
	Number result;
	result._sign = 1;
	result._int = _int;
	result._dec = _dec;
	return result;
}

void Number::trace(std::ostream &out) const
{
	out << "result._sign " << _sign << std::endl;
	out << "result._int " << _int << std::endl;
	out << "result._dec " << _dec << std::endl;
}

bool operator!=(const Number &left, const Number &right)
{
	return !(left == right);
}

bool operator>(const Number &left, const Number &right)
{
	if (left._sign > right._sign) {
		return true;
	}

	if (left._sign < right._sign) {
		return false;
	}

	if (left == right) {
		return false;
	}

	if (left._sign > 0) {
		if (left._int > right._int) {
			return true;
		}
		if (left._int == right._int && left._dec > right._dec) {
			return true;
		}
	} else {
		if (left._int < right._int) {
			return true;
		}
		if (left._int == right._int && left._dec < right._dec) {
			return true;
		}
	}

	return false;
}

bool operator==(const Number &left, const Number &right)
{
	if (left._sign == right._sign &&
		left._int == right._int &&
		left._dec == right._dec)
	{
		return true;
	}
	return false;
}

Number operator+(const Number &left, const Number &right)
{
	Number result;

	if (left._sign == right._sign) {
		result._sign = left._sign;
		result._int = left._int + right._int;
		result._dec = left._dec + right._dec;

		int over = static_cast<int>(result._dec);
		result._dec -= over;
		result._int += over;
		return result;
	}

	if (left == right) {
		result._sign = 1;
		result._int = 0;
		result._dec;
		return result;
	}

	Number max;
	Number min;

	if (left.abs() > right.abs()) {
		result._sign = left._sign;
		max = left.abs();
		min = right.abs();
	} else {
		result._sign = right._sign;
		max = right.abs();
		min = left.abs();
	}

	result._int = max._int - min._int;
	result._dec = max._dec - min._dec;
	if (result._dec < 0) {
		--result._int;
		result._dec = 1 + result._dec;
	}

	if (result.abs() == Number(0)) {
		result._sign = 1;
	}
	//result.trace(std::cout);

	return result;
}

Number operator-(const Number &left, const Number &right)
{
	Number modRight(right);
	modRight._sign *= (-1);
	return (left + modRight);
}

Number operator*(const Number &left, const Number &right)
{
	Number result;
	result._sign = left._sign * right._sign;
	result._int = left._int *right._int;
	result._dec = left._dec*right._dec + left._dec*right._int + left._int*right._dec;

	int64_t over = static_cast<int64_t>(result._dec);
	result._int += over;
	result._dec -= over;

	if (result._int == 0 && result._dec == 0) {
		result._sign = 1;
	}
	//result.trace(std::cout);
	return result;
}

Number operator/(const Number &left, const Number &right)
{
	Number result;
	if (right.abs() == Number(0)) {
		result._sign = -1;
		result._int = 0;
		result._dec = 0;
		return result;
	}
	
	if (left.abs() == Number(0)) {
		result._sign = 1;
		result._int = 0;
		result._dec = 0;
		return result;
	}

	result._sign = right._sign * left._sign;

	if (right.abs() == left.abs()) {
		result._int = 1;
		result._dec = 0;
		return result;
	}

	if (right.abs() > left.abs()) {
		result._int = 0;

		if (right._int == 0) {
			result._dec = left._dec / right._dec;
			return result;
		}

		double l = left._int*1000 + static_cast<int>(std::round(left._dec*1000));
		int64_t r = right._int*1000 + static_cast<int>(std::round(right._dec*1000));
		result._dec = l/r;
		return result;
	}

	long double pow = 1000;
	int64_t r = right._int*pow + static_cast<int>(std::round(right._dec*pow));

	while (r == 0) {
		pow*=10;
		r = right._int*pow + static_cast<int>(std::round(right._dec*pow));
	}

	int64_t l = left._int*pow + static_cast<int>(std::round(left._dec*pow));
	result._int = l/r;
	result._dec = static_cast<double>(l%r)/r;
	return result;
}

std::ostream &operator<<(std::ostream &out, const Number &num)
{
	out << num.toString();
	return out;
}
