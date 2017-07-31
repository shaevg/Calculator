#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>

/*
 * Лучше использовать CLN (Class Library for Numbers [GiNaC]) для вычислений
 */

class Number {
public:
	Number();
	Number(const Number& num);
	Number(std::string num);
	Number(const double &num);
	Number(const int& num);
	std::string toString() const;
	bool isInfinite();
	Number& operator= (const Number& num);
	Number abs() const;
	void trace(std::ostream& out) const;

	friend std::ostream& operator<< (std::ostream& out, const Number& num);
	friend bool operator> (const Number& left, const Number& right);
	friend bool operator== (const Number& left, const Number& right);
	friend bool operator!= (const Number& left, const Number& right);

	friend Number operator+ (const Number& left, const Number& right);
	friend Number operator- (const Number& left, const Number& right);
	friend Number operator* (const Number& left, const Number& right);
	friend Number operator/ (const Number& left, const Number& right);

private:
	int _sign;
	int64_t _int;
	double _dec;
};

#endif // NUMBER_H
