#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "mySqlist_2.h"

class Student
{
public:
	std::string number, name, sex;
	int score;

	Student() 
	{
		std::cout << "成功构造未初始化学生。" << std::endl;
	}

	Student(std::string number, std::string name, std::string sex, int score) : number(number), name(name), sex(sex), score(score)
	{
		if (debug)
		{
			std::cout << "成功构造学生：" << name << "。" << std::endl;
		}
	}

	bool operator<(const Student &stu) const
	{
		return number.length() < stu.number.length() || (number.length() == stu.number.length() && number < stu.number);
	}
};

std::ostream &operator<<(std::ostream &os, Student &stu)
{
	os << stu.number << "\t" << stu.name << "\t" << stu.sex << "\t" << stu.score << std::endl;
	return os;
}

void ask()
{
	std::cout << "==================================================" << std::endl;
	std::cout << "1: 学生信息线性表的建立" << std::endl;
	std::cout << "2: 插入学生信息" << std::endl;
	std::cout << "3: 查询学生信息" << std::endl;
	std::cout << "4: 删除学生信息" << std::endl;
	std::cout << "5: 输出所有学生信息" << std::endl;
	std::cout << "0: 退出学生管理系统" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "请选择0~5" << std::endl
			  << std::endl;
	std::cout << "请选择：";
}

void listPrint(seqList<Student> *&myList)
{
	if (!myList)
	{
		std::cout << "请先创建学生信息线性表。" << std::endl;
		return;
	}

	std::cout << "**************************************************" << std::endl;
	std::cout << "\t\t输出所有学生信息" << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "学号\t姓名\t性别\t成绩" << std::endl;
	myList->print();
}

void listCreate(seqList<Student> *&myList)
{
	if (myList)
	{
		std::cout << "学生信息线性表已存在，是否删除？" << std::endl;
		std::cout << "1: 是" << std::endl;
		std::cout << "2: 否" << std::endl;
		std::cout << "请选择1或2：" << std::endl;
		int select;
		std::cin >> select;

		while (select != 1 && select != 2)
		{
			std::cout << "错误，请重新输入。" << std::endl;
			std::cin >> select;
		}

		if (select == 1)
		{
			delete myList;
		}
		else
		{
			return;
		}
	}
	myList = nullptr;

	std::cout << "**************************************************" << std::endl;
	std::cout << "学生信息线性表的建立" << std::endl;
	std::cout << "**************************************************" << std::endl;

	std::cout << "有几位学生？请输入：" << std::endl;
	int n;
	std::cin >> n;
	while (n <= 0)
	{
		std::cout << "错误输入！请重新输入学生个数。" << std::endl;
		std::cin >> n;
	}

	myList = new seqList<Student>(n);

	std::cout << "以下请输入这" << n << "个学生的信息：" << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	for (int i = 1; i <= n; ++i)
	{
		std::string number, name, sex;
		int score;
		std::cout << "第" << i << "个学生信息为：" << std::endl;
		std::cout << "学号：";
		std::cin >> number;

		std::cout << "姓名：";
		std::cin >> name;

		std::cout << "性别：";
		std::cin >> sex;

		std::cout << "成绩：";
		std::cin >> score;

		myList->insert(Student(number, name, sex, score));
		std::cout << "==================================================" << std::endl;
	}
	std::cout << "--------------------------------------------------" << std::endl;
}

void listInsert(seqList<Student> *&myList)
{
	if (!myList)
	{
		std::cout << "请先创建学生信息线性表。" << std::endl;
		return;
	}

	if (myList->length >= myList->capacity)
	{
		std::cout << "学生信息线性表已满，无法插入。" << std::endl;
		return;
	}

	std::cout << "请输入要插入的学生数据的位置：";
	int index;
	std::cin >> index;

	while (index < 0 || index > myList->length)
	{
		std::cout << "错误，请重新输入。" << std::endl;
		std::cin >> index;
	}

	std::cout << "输入学生信息：" << std::endl;
	std::string number, name, sex;
	int score;
	std::cout << "学号：";
	std::cin >> number;
	std::cout << "姓名：";
	std::cin >> name;
	std::cout << "性别：";
	std::cin >> sex;
	std::cout << "成绩：";
	std::cin >> score;

	Student temp(number, name, sex, score);
	myList->insert(temp, index);

	listPrint(myList);
}

std::vector<int> listSearchByNumber(seqList<Student> *&myList)
{
	std::cout << "请输入要查询的学号：" << std::endl;
	std::string number;
	std::cin >> number;

	std::vector<int> searched;

	for (int i = 0; i < myList->length; ++i)
	{
		if (myList->data[i].number == number)
		{
			searched.emplace_back(i);
		}
	}

	if (searched.size() == 0)
	{
		std::cout << "未找到学号为" << number << "的学生。" << std::endl;
	}
	else
	{
		std::cout << "您要查询的学生为：" << std::endl;
		std::cout << "学号\t姓名\t性别\t成绩" << std::endl;
		for (int i = 0; i < searched.size(); ++i)
		{
			std::cout << myList->data[searched[i]] << std::endl;
		}
	}

	return searched;
}

std::vector<int> listSearchByName(seqList<Student> *&myList)
{
	std::cout << "请输入要查询的姓名：" << std::endl;
	std::string name;
	std::cin >> name;

	std::vector<int> searched;

	for (int i = 0; i < myList->length; ++i)
	{
		if (myList->data[i].name == name)
		{
			searched.emplace_back(i);
		}
	}

	if (searched.size() == 0)
	{
		std::cout << "未找到姓名为" << name << "的学生。" << std::endl;
	}
	else
	{
		std::cout << "您要查询的学生为：" << std::endl;
		std::cout << "学号\t姓名\t性别\t成绩" << std::endl;
		for (int i = 0; i < searched.size(); ++i)
		{
			std::cout << myList->data[searched[i]] << std::endl;
		}
	}

	return searched;
}

std::vector<int> listSearch(seqList<Student> *&myList)
{
	if (!myList)
	{
		std::cout << "请先创建学生信息线性表。" << std::endl;
		return std::vector<int>();
	}

	std::cout << "请输入要查询的方式：" << std::endl;
	std::cout << "1: 按学号查询" << std::endl;
	std::cout << "2: 按姓名查询" << std::endl;
	std::cout << "==================================================" << std::endl;
	std::cout << "请选择1或2：";
	int select;
	std::cin >> select;
	while (select != 1 && select != 2)
	{
		std::cout << "错误，请重新输入。" << std::endl;
		std::cin >> select;
	}

	if (select == 1)
	{
		return listSearchByNumber(myList);
	}
	else if (select == 2)
	{
		return listSearchByName(myList);
	}

	return std::vector<int>();
}

template <typename T>
void listDelete(seqList<T> *&myList)
{
	if (!myList)
	{
		std::cout << "请先创建学生信息线性表。" << std::endl;
		return;
	}

	std::cout << "请先查找要删除的学生信息：" << std::endl;
	std::vector<int> searched = listSearch(myList);

	if (searched.size() == 0)
	{
		return;
	}

	std::vector<int> needDelete;
	std::cout << "请选择要删除的学生信息：" << std::endl;
	for (int i = 0; i < searched.size(); ++i)
	{
		std::cout << i + 1 << ": " << myList->data[searched[i]] << std::endl;
	}
	std::cout << "==================================================" << std::endl;
	std::cout << "请选择1~" << searched.size() << "：";
	int select;
	std::cin >> select;
	while (select < 1 || select > searched.size())
	{
		std::cout << "错误，请重新输入。" << std::endl;
		std::cin >> select;
	}

	myList->remove(searched[select - 1]);
	std::cout << "删除成功。" << std::endl;
}

void myProcess()
{
	ask();
	static seqList<Student> *myList = nullptr;
	int select;
	std::cin >> select;
	while (select > 5 || select < 0)
	{
		std::cout << "错误，请重新输入。" << std::endl;
		std::cin >> select;
	}

	switch (select)
	{
	case 0:
		std::cout << "退出学生管理系统。" << std::endl;
		system("pause");
		exit(0);
		break;

	case 1:
		listCreate(myList);
		break;

	case 2:
		listInsert(myList);
		break;

	case 3:
		listSearch(myList);
		break;

	case 4:
		listDelete(myList);
		break;

	case 5:
		listPrint(myList);
		break;

	default:
		break;
	}

	system("pause");
}

void work()
{
	while (true)
	{
		myProcess();
	}
}

void setConsoleUTF8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

int main()
{
	setConsoleUTF8();

	std::cout << "\t\t学生信息管理系统" << std::endl;

	work();

	return 0;
}