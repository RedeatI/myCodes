#include <iostream>
#include <stack>
using namespace std;

void work()
{
	cout << "input a number then convert to binary : ";
	int num;
	cin >> num;
	stack<int> binary;
	while (num > 0)
	{
		binary.emplace(num % 2);
		num /= 2;
	}
	cout << "the binary is : ";
	while (!binary.empty())
	{
		cout << binary.top();
		binary.pop();
	}
}

int main()
{
	work();
	return 0;
}