#include <iostream>
#include <stack>
using namespace std;

void work()
{
	stack<int> odd, even;
	int n;
	cout << "please input the num of numbers : ";
	cin >> n;
	cout << "input numbers : ";
	while (n--)
	{
		int num;
		cin >> num;
		if (num & 1)
		{
			odd.emplace(num);
		}
		else
		{
			even.emplace(num);
		}
	}
	cout << "the odd : ";
	while (!odd.empty())
	{
		cout << odd.top() << " ";
		odd.pop();
	}
	cout << "\nthe even : ";
	while (!even.empty())
	{
		cout << even.top() << " ";
		even.pop();
	}
}

int main()
{
	work();
	return 0;
}