#include <iostream>
#include "Expression.h"

using namespace std;

int main()
{
	Expression e;

	cin >> e;

	cout << 'g';

	try {
		cout << e.calculate();
	}
	catch(...)
	{
		cout << "Error";
	}

	return 0;
}
