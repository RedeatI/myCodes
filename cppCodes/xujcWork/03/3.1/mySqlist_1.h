#pragma once
#include <iostream>
#include <vector>

template <typename T>
class seqList
{
public:
    std::vector<T> data;
    int length;
    int capacity;

    seqList(int capacity)
    {
        this->capacity = capacity;
        data.resize(capacity);
        length = 0;
        std::cout << "Successed initalized seqList. The List's capacity is " << capacity << std::endl;
    }
    
    seqList(std::vector<T> numbers)
    {
    	this->capacity = numbers.size();
    	data = numbers;
    	length = numbers.size();
    	std::cout << "Successed initalized seqList. The List's capacity is " << capacity << std::endl;
	}

    void insert(T value)
    {
        if (length == capacity)
        {
            std::cout << "Error: list is full" << std::endl;
            return;
        }

        int index = 0;
        while (index < length && data[index] < value)
        {
            ++index;
        }

        for (int i = length; i > index; --i)
        {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++length;
        std::cout << "Insert success." << std::endl;
    }

    void remove(int index)
    {
        if (index < 0 || index >= length)
        {
            std::cout << "Error: index out of range" << std::endl;
            return;
        }

        for (int i = index; i < length - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        --length;
        
        std::cout << "Remove success." << std::endl;
    }

    int get(int index)
    {
        if (index < 0 || index >= length)
        {
            return -1;
        }

        return data[index];
    }
    
    void print()
    {
    	std::cout << "List:" << std::endl;
    	for (int i = 0; i < length; ++i)
    	{
    		std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}
	
	void search(int number)
	{
		std::vector<int> searched; 
		for (int i = 0; i < length; ++i)
		{
			if (data[i] == number)
			{
				searched.emplace_back(i);
			}
		}
		
		if (searched.size() == 0)
		{
			std::cout << "The number is not in the list." << std::endl;
		}
		else
		{
			std::cout << "Find the number in index: ";
			for (auto index : searched)
			{
				std::cout << index << " ";
			}
			std::cout << std::endl;
		}
	}
};