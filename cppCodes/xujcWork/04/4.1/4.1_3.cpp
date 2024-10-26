#include <iostream>
#include <string>
#include <stack>
#include <map>
using namespace std;

map<char, int> opts = { {'+', 0}, {'-', 0}, {'*', 1 }, {'/', 1 }, {'(', -1} };

double cul(char opt, double num1, double num2)
{
	if (opt == '*')
	{
		return num1 * num2;
	}
	else if (opt == '/')
	{
		if (num2 == 0)
		{
			cout << "you can't / 0";
			exit(1);
		}
		return num1 / num2;
	}
	else if (opt == '+')
	{
		return num1 + num2;
	}
	else if (opt == '-')
	{
		return num1 - num2;
	}
	else
	{
		cout << "input format error.";
		exit(1);
	}
}

void work()
{
	stack<double> num;
	stack<char> opt;
	string t;
	cin >> t;
	int temp = 0;
	bool start = false;
	for (int i = 0; i < t.length(); ++i)
	{
		char c = t[i];

		if (!start)
		{
			if (c == '#')
			{
				start = true;
			}
			continue;
		}

		if (c == '#')
		{
			while (!opt.empty())
			{
				if (num.size() < 2)
				{
					cout << "input format error.";
					exit(1);
				}
				int num2 = num.top();
				num.pop();
				int num1 = num.top();
				num.pop();
				num.emplace(cul(opt.top(), num1, num2));
				opt.pop();
			}
			break;
		}

		if (!(c >= '0' && c <= '9'))
		{
			if (opt.empty() || c == '(')
			{
				opt.emplace(c);
			}
			else if (c == ')')
			{
				char t_opt = opt.top();
				while (t_opt != '(')
				{
					if (num.size() < 2)
					{
						cout << "input format error.";
						exit(1);
					}
					int num2 = num.top();
					num.pop();
					int num1 = num.top();
					num.pop();
					num.emplace(cul(t_opt, num1, num2));
					opt.pop();
					t_opt = opt.top();
				}
				opt.pop();
			}
			else
			{
				while (!opt.empty() && opts[c] <= opts[opt.top()])
				{
					char t_opt = opt.top();
					opt.pop();
					int num2 = num.top();
					num.pop();
					int num1 = num.top();
					num.pop();
					num.emplace(cul(t_opt, num1, num2));
				}
				opt.emplace(c);
			}
		}
		else
		{
			temp = t[i] - '0';
			while (t[i + 1] >= '0' && t[i + 1] <= '9')
			{
				temp = temp * 10 + (t[++i] - '0');
			}
			num.emplace(temp);
		}


	}

	if (num.size() != 1 || start == false)
	{
		cout << "input format error.";
		exit(1);
	}

	cout << "result is : " << num.top() << endl;
}

int main()
{
	while (true)
	{
		work();
	}
	return 0;
}
