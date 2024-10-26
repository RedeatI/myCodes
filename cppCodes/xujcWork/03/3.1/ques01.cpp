#include <iostream>
#include <vector>
#include <algorithm>
#include "mySqlist_1.h"

seqList<int> createList()
{
	std::cout << "------------------------------------------" << std::endl;
    std::cout << "Please input the capacity of sqlist that you want:" << std::endl;
    int cpc;
    std::cin >> cpc;
    seqList<int> myList(cpc);
    return myList;
    std::cout << "------------------------------------------" << std::endl;
}

void ask()
{
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Funtions:" << std::endl;
	std::cout << "1: Delete number by index." << std::endl;
	std::cout << "2: Insert a number." << std::endl;
	std::cout << "3: Search a number by index." << std::endl;
	std::cout << "4: Print List." << std::endl;
	std::cout << "5: Find is a number in the list." << std::endl;
	std::cout << "6: Get the length of the list." << std::endl;
	std::cout << "7: Show help." << std::endl;
	std::cout << "0: Exit program." << std::endl;
	std::cout << "------------------------------------------" << std::endl;
}

void listDelete(seqList<int> &myList)
{
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Please input the index that you want to delete." << std::endl;
	int n;
	std::cin >> n;
	myList.remove(n);
	std::cout << "------------------------------------------" << std::endl;
}

void listInsert(seqList<int> &myList)
{
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Please input the number that you want to insert." << std::endl;
	int num;
	std::cin >> num;
	myList.insert(num);
	std::cout << "------------------------------------------" << std::endl;
}

void listSearch(seqList<int> &myList)
{
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Please input the index that you want to search." << std::endl;
	int n;
	std::cin >> n;
	int num = myList.get(n);
	if (num == -1)
	{
		std::cout << "Index out of range." << std::endl;
	}
	else
	{
		std::cout << "Index:" << n << "'s number is:" << num << "." << std::endl; 
	}
	std::cout << "------------------------------------------" << std::endl;
}

void listPrint(seqList<int> &myList)
{
	std::cout << "------------------------------------------" << std::endl;
	myList.print();
	std::cout << "------------------------------------------" << std::endl;
}

void listFindNumber(seqList<int> &myList)
{
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "Please input the number that you want to find." << std::endl;
	int n;
	std::cin >> n;
	myList.search(n);
	std::cout << "------------------------------------------" << std::endl;
}

void listGetLength(seqList<int> &myList)
{
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "List's length is:" << myList.length << "." << std::endl;
	std::cout << "------------------------------------------" << std::endl;
}

void myProcess(seqList<int> &myList)
{
	int select;
	std::cin >> select;
	while(select > 7 || select < 0)
	{
		std::cout << "Invalid input...Please input again." << std::endl;
		std::cin >> select;
	}
	
	switch(select)
	{
		case 0:
			exit(0);
			break;
			
		case 1:
			listDelete(myList);
			break;
			
		case 2:
			listInsert(myList);
			break;
			
		case 3:
			listSearch(myList);
			break;
			
		case 4:
			listPrint(myList);
			break;
		
		case 5:
			listFindNumber(myList);
			break;
			
		case 6:
			listGetLength(myList);
			break;
			
		case 7:
			ask();
			break;
	}
}

void work()
{
    std::vector<int> numbers;
	int n;
	std::cout << "Input numbers... 0 to stop." << std::endl;
	std::cin >> n;
	while(n != 0)
	{
		numbers.emplace_back(n);
		std::cin >> n;
	}
	
	sort(numbers.begin(), numbers.end());
	
	seqList<int> myList(numbers);
	
	ask();
	while(true)
	{
		myProcess(myList);
	}
}

int main()
{
    work();
	
    return 0;
}
