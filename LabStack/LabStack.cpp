#include <iostream>
#include "Expression.h"
#include <conio.h>

using namespace std;

int main()
{
	while (true)
	{
		system("cls");
		Expression e;
		cout << "Please input expression: ";
		cin >> e;

		try {
			cout << "RPN: " << e.toRPN() << endl;
			double result = e.calculate();
			if (!e.getErrors())
			{
				cout << "Result: " << result;
			}
		}
		catch (vector< pair<int, int> > table)
		{
			cout << "Error with brackets, table: " << endl;
			for (pair<int, int> p : table)
				cout << p.first << ' ' << p.second << endl;
		}
		catch (string s)
		{
			cout << s;
		}
		catch (PopEmptyStackException e)
		{
			cout << "Not enough operands";
		}
		_getch();
	}


	return 0;
}
