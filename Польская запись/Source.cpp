#include <iostream>
#include <stack>


using namespace std;

int check(string test)
{
	int errorsCounter = 0;
	stack<char> myStackFirst;
	for (int i = 0; i < test.length(); i++)
	{
		switch (test[i])
		{
		case ' ':
			errorsCounter++;
			break;
		case '(':
			myStackFirst.push(i);
			break;
		case ')':
			if (myStackFirst.empty())
			{
				errorsCounter++;
			}
			else
			{
				myStackFirst.pop();
			}
			break;
		case '/':
			if (i + 1 < test.length() && test[i + 1] == '0')
			{
				errorsCounter++;
			}
		case '+':
		case '-':
		case '*':
			if ((i - 1) >= 0 && (i + 1) < test.length())
			{
				if (test[i - 1] == '*' ||
					test[i + 1] == '*' ||
					test[i - 1] == '/' ||
					test[i + 1] == '/' ||
					test[i - 1] == '-' ||
					test[i + 1] == '-' ||
					test[i - 1] == '+' ||
					test[i + 1] == '+')
				{
					errorsCounter++;
				}
			}
			else
			{
				errorsCounter++;
			}
			break;
		default:
			continue;
		}


	}
	while (!myStackFirst.empty())
	{
		errorsCounter++;
		myStackFirst.pop();
	}
	cout << "Amout of quantity: " << errorsCounter << endl;
	return errorsCounter;
}

string pol(string str)
{
	int counter_brackets = 0;
	stack<char> myStack;
	string myString;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (!myStack.empty() && (myStack.top() == '*' || myStack.top() == '/'))
			{
				myString.push_back(myStack.top());
				myStack.pop();
				myStack.push(str[i]);
				continue;
			}
			myStack.push(str[i]);
			continue;
		}

		if (str[i] == '*' || str[i] == '/')
		{
			myStack.push(str[i]);
			continue;
		}

		if (str[i] == '(')
		{
			if (counter_brackets == 0 && !myStack.empty())
			{
				char helper = myStack.top();
				myStack.pop();
				myString.push_back(myStack.top());
				myStack.pop();
				myStack.push(helper);
			}
			myStack.push(str[i]);
			counter_brackets++;
			continue;
		}

		if (str[i] == ')')
		{
			counter_brackets--;

			while (myStack.top() != '(')
			{
				myString.push_back(myStack.top());
				myStack.pop();
			}
			myStack.pop();

			while (!myStack.empty())
			{
				if (myStack.top() == '(')
				{
					break;
				}
				myString.push_back(myStack.top());
				myStack.pop();
			}

			continue;
		}

		myString.push_back(str[i]);
	}

	while (!myStack.empty())
	{
		myString.push_back(myStack.top());
		myStack.pop();
	}
	cout<<"my str: " << myString << endl;
	cout << "old str:" << str << endl;

	return myString;
}

int result(string str)
{
	stack<int> myStack;

	

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '+')
		{

			int second = myStack.top();
			myStack.pop();

			int first = myStack.top();
			myStack.pop();

			myStack.push(first + second);
			continue;
		}

		if (str[i] == '-')
		{
			int second = myStack.top();
			myStack.pop();

			int first = myStack.top();
			myStack.pop();

			myStack.push(first - second);
			continue;
		}

		if (str[i] == '*')
		{
			int second = myStack.top();
			myStack.pop();

			int first = myStack.top();
			myStack.pop();

			myStack.push(first * second);
			continue;
		}

		if (str[i] == '/')
		{
			int second = myStack.top();
			myStack.pop();

			int first = myStack.top();
			myStack.pop();

			myStack.push(first / second);
			continue;
		}

		myStack.push(str[i] - '0');
		
	}
	return myStack.top();
}

int main()
{
	string example = "(5*(7-2))+2-(2*4+1)"; //18
	
	if (check(example) == 0)
	{
		cout << result(pol(example));
	}
	cout << endl;

	string another_exampler = "(1+2-4*(3-1))";//-5

	if (check(example) == 0)
	{
		cout << result(pol(another_exampler));
	}
	cout << endl<<endl;

	string fail_brack1 = "((1+2)";
	string fail_brack2 = "(1+2))";
	check(fail_brack1);
	check(fail_brack2);
	cout << endl;

	string fail_double_sign1 = "2**3";
	string fail_double_sign2 = "2--3";
	string fail_double_sign3 = "2++3";
	check(fail_double_sign1);
	check(fail_double_sign2);
	check(fail_double_sign3);
	cout << endl;
	return 0;
}