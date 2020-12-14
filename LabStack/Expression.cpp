#include "Expression.h"

string getClearString(string str)
{
	string s = "";
	for (char c : str)
	{
		if (c == '(' || c == ')' || c == '<' || c == '>' ||
			c == '{' || c == '}' || c == '[' || c == ']')
			s += c;
	}
	return s;
}

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

int isNumber(string s)
{
	bool isNegative = false;
	if (s[0] == '-' && s.size() > 1)
	{
		isNegative = true;
		s = s.substr(1, s.size() - 1);
	}

	for (int i = 0; i < s.size(); i++)
		if (!isdigit(s[i]))
			return 0;

	return isNegative ? -1 : 1;
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



Expression::Expression(string ex) : expr(ex), countOfError(0)
{
}

vector< pair<int, int> > Expression::checkBrackets(string str)
{
	str = getClearString(str);
	Stack<int> brackets(100);
	countOfError = 0;
	vector< pair<int, int> > table;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
			brackets.push(i+1);
		else if (str[i] == ')')
		{
			if (!brackets.isEmpty())
				table.push_back(pair<int, int>(brackets.pop(), i+1));
			else {
				table.push_back(pair<int, int>(0, i+1));
				countOfError++;
			}
		}
	}
	while (!brackets.isEmpty())
	{
		table.push_back(pair<int, int>(brackets.pop(), 0));
		countOfError++;
	}

	return table;
}

int Expression::calculate()
{
	if (expr.empty())
		return 0;
	vector< pair<int, int> > table = checkBrackets(expr);

	if (countOfError)
		throw table;

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

	for (int i = 0; i < v.size(); i++)
	{
		if (isNumber(v[i]) == -1)
		{
			v[i] = v[i].substr(1, v[i].size() - 1);
			v.insert(v.begin() + i, "-");
			v.insert(v.begin() + i, "0");
			i++;
		}
	}

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