#include <iostream>
#include "Expression.h"
#include <conio.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	while (true)
	{
		system("cls");
		Expression e;
		cin >> e;

		try {
			int result = e.calculate();
			if (!e.getErrors())
			{
				cout << "RPN: " << e.toRPN() << endl << result;
			}
		}
		catch (vector< pair<int, int> > table)
		{
			cout << "Неправильная расстановка скобок, таблица соответствия: " << endl;
			for (pair<int, int> p : table)
				cout << p.first << ' ' << p.second << endl;
		}
		catch (string s)
		{
			cout << s;
		}
		catch (PopEmptyStackException e)
		{
			cout << "Недостаточно операндов";
		}
		_getch();
	}

	return 0;
}
