#include "Expression.h"

vector<string> split(string s)
{
	vector<string> result;
	if (s.empty())
		return result;

	int begin = 0, end = 0;
	while (begin < s.size())
	{
		auto it = find(s.begin() + begin, s.end(), ' ');
		end = distance(s.begin(), it);
		result.push_back(s.substr(begin, end - begin));
		begin = end + 1;
	}
	return result;
}

bool isNumber(string s)
{
	for (char c : s)
		if (!isdigit(c))
			return false;
	return true;
}

void doOperation(Stack<int>& s, string operation)
{
	if (operation == "+")
	{
		int second = s.pop();
		int first = s.pop();
		s.push(first + second);
		return;
	}
	if (operation == "-")
	{
		int second = s.pop();
		int first = s.pop();
		s.push(first - second);
		return;
	}
	if (operation == "*")
	{
		int second = s.pop();
		int first = s.pop();
		s.push(first * second);
		return;
	}
	if (operation == "/")
	{
		int second = s.pop();
		int first = s.pop();
		s.push(first / second);
		return;
	}
	if (operation == "^")
	{
		int second = s.pop();
		int first = s.pop();
		s.push(pow(first, second));
		return;
	}
}



Expression::Expression(string ex) : expr(ex)
{
}

int Expression::calculate() const
{
	if (!checkBrackets())
		throw "Brackets Error";

	Stack<int> s(100);
	string str = toRPN();
	vector<string> v = split(str);

	for (string op : v)
	{
		if (isNumber(op))
			s.push(stoi(op));
		else doOperation(s, op);
	}

	return s.pop();

}

string Expression::toRPN() const
{
	string result = "";
	vector<string> v = split(expr);
	Stack<Operation> s(20);

	for (string str : v)
	{
		if (isNumber(str))
			result += str + ' ';

		else if (str == "(")
			s.push(Operation(str[0]));

		else if (str == ")")
		{
			while (s.peek() != '(')
			{
				result += s.pop();
				result += ' ';
			}
			s.pop();
		}

		else if (Operation::isOperation(str[0]))
		{
			Operation op(str[0]);
			while (s.peek() >= op && !s.isEmpty())
			{
				result += s.pop();
				result += ' ';
			}
			s.push(op);
		}
	}


	while (!s.isEmpty())
	{
		result += s.pop();
		result += ' ';
	}

	return result;
}

bool Expression::checkBrackets() const
{
	return true;
}

std::ostream& operator<<(std::ostream& out, const Expression& exp)
{
	out << exp.expr;
	return out;
}

std::istream& operator>>(std::istream& in, Expression& exp)
{
	std::getline(in, exp.expr);
	return in;
}
