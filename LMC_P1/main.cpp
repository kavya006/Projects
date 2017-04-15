#include "iostream"
#include "string"

#include "check_expression/check_expression.cpp"
#include "check_string/check_string.cpp"

using namespace std;
int main()
{
	string expression;
	cin >> expression;
	if(check_expression(expression) == 0)
	{
		cout << "Wrong Expression" << endl;
		return 0;
	}
	NFA nfa(expression);
	int TestCases;
	cin >> TestCases;
	string input;
	for (int i = 0; i < TestCases; ++i)
	{
		cin >> input;
		if(check_string(input,nfa) == 1)
		{
			cout << "Yes" << endl;
		}
		else 
		{
			cout << "No" << endl;
		}
	}
}
