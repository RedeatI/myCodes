#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int QUEUESIZE = 20;

class Student {
public:
	string stuNum, name;
	friend ostream& operator << (ostream& os, Student& stu)
	{
		os << stu.stuNum << '\t' << stu.name;
		return os;
	}
};

template <typename T>
class myQueue
{
private:
	vector<T> data;
	int front, tail, size;
public:
	myQueue()
	{
		size = QUEUESIZE;
		data.resize(QUEUESIZE);
		front = 0;
		tail = 1;
	}

	myQueue(int size) {
		this->size = size;
		data.resize(size);
		front = 0;
		tail = 1;
	}

	void resize(int sz)
	{
		data.resize(sz);
		this->size = sz;
	}

	bool isEmpty()
	{
		return (front + 1) % size == tail;
	}

	void push(T data)
	{
		if (front != tail)
		{
			this->data[tail] = data;
			tail = (tail + 1) % size;
		}
		else
		{
			cout << "queue is full.\n";
		}
	}

	void pop()
	{
		if (isEmpty())
		{
			cout << "queue is empty.\n";
			return;
		}
		else
		{
			front = (front + 1) % size;
		}
	}

	void print()
	{
		for (int i = (front + 1) % size; i != tail; i = (i + 1) % size)
		{
			cout << data[i] << '\n';
		}
	}
};

myQueue<Student> que;

void push()
{
	cout << "排队学生人数为：";
	int n;
	cin >> n;
	while (n--)
	{
		Student temp;
		cout << "学号：";
		cin >> temp.stuNum;
		cout << "姓名：";
		cin >> temp.name;
		cout << "-----------------------\n";
		que.push(temp);
	}
}

void pop()
{
	que.pop();
}

void print()
{
	que.print();
}

void myExit()
{
	if (!que.isEmpty())
	{
		cout << "已杀死所有还在排队的\n";
	}
	exit(0);
}

void work()
{
	cout << "\t\t学生答疑系统\n";
	cout << "1.排队\t2.答疑\t3.查看排队名单\t4.退出\n";
	cout << "请选择：";

	int sel;
	cin >> sel;

	switch (sel)
	{
	case(1):
		push();
		break;
	case(2):
		pop();
		break;
	case(3):
		print();
		break;
	case(4):
		myExit();
		break;
	default:
		cout << "error select.\n";
		break;
	}
}

int main()
{
	while (true)
	{
		work();
	}
	return 0;
}