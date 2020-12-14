#include <iostream>
#include "Expression.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	Expression e;
	cin >> e;

	try { cout << e.calculate(); }
	catch (vector< pair<int, int> > table)
	{
		cout << "Неправильная расстановка скобок, таблица соответствия: " << endl;
		for (pair<int, int> p : table)
			cout << p.first << ' ' << p.second << endl;
	}

	return 0;
}
