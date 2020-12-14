#pragma once

#include <string>
#include <vector>
#include "Stack.h"
#include <iostream>


using std::string;
using std::vector;
using std::pair;

struct Operation
{
	Operation()
	{

	}

	Operation(char c)
	{
		oper = c;

		if (c == '(' || c == ')')
			priority = 0;

		if (c == '+' || c == '-')
			priority = 1;

		if (c == '/' || c == '*')
			priority = 2;

		if (c == '^')
			priority = 3;
	}
	
	bool operator<(Operation& sec)
	{
		return priority < sec.priority;
	}

	bool operator>(Operation& sec)
	{
		return priority > sec.priority;
	}

	bool operator<=(Operation& sec)
	{
		return priority <= sec.priority;
	}

	bool operator>=(Operation& sec)
	{
		return priority >= sec.priority;
	}
	
	bool operator==(Operation& sec)
	{
		return priority == sec.priority;
	}	

	operator char()
	{
		return oper;
	}


	static bool isOperation(char c)
	{
		return (c == '+' || c == '-' || c == '/' || c == '*' || c == '/' || c == '^');
	}

	char oper;
	int priority;
};

class Expression
{
public:
	Expression(string ex = "");

	int calculate();

	friend std::ostream& operator<<(std::ostream& out, const Expression& exp);
	friend std::istream& operator>>(std::istream& in, Expression& exp);

private:
	vector< pair<int, int> > checkBrackets(string str);
	string toRPN() const;

	string expr;
	int countOfError;
};

