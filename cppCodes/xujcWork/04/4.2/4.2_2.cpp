#include <iostream>
#include <string>
#include <queue>
using namespace std;

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
class Node
{
public:
	T data;
	Node<T>* next;

	Node() :next(nullptr) {};

	Node(T data)
	{
		this->data = data;
		next = nullptr;
	}
};


template <typename T>
class myQueue
{
public:
	Node<T>* head;

	bool isEmpty()
	{
		return head->next == nullptr;
	}

	myQueue()
	{
		head = new Node<T>();
	}

	void push(T data)
	{
		Node<T>* temp = head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new Node<T>(data);
	}

	void pop()
	{
		if (isEmpty())
		{
			cout << "queue is empty.\n";
			return;
		}
		Node<T>* temp = head->next;
		head->next = head->next->next;
		delete temp;
	}

	void print()
	{
		Node<T>* temp = head->next;
		while (temp)
		{
			cout << temp->data << '\n';
			temp = temp->next;
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