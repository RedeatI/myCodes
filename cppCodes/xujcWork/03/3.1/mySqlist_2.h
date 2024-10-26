#pragma once
bool debug = true;

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
		if (debug)
		{
			std::cout << "成功初始化顺序表，容量为：" << capacity << std::endl;
		}
	}

	seqList(std::vector<T> newDatas)
	{
		this->capacity = newDatas.size();
		data = newDatas;
		length = newDatas.size();
		if (debug)
		{
			std::cout << "成功初始化顺序表，容量为：" << capacity << std::endl;
		}
	}

	seqList(seqList &list)
	{
		this->capacity = list.capacity;
		this->length = list.length;
		this->data = list.data;
		if (debug)
		{
			std::cout << "成功初始化顺序表，容量为：" << capacity << std::endl;
		}
	}

	~seqList()
	{
		if (debug)
		{
			std::cout << "成功删除顺序表。" << std::endl;
		}
	}

	void insert(T element)
	{
		if (length >= capacity)
		{
			throw "List is full.";
		}

		data[length] = element;
		++length;
	}

	void insert(T element, int index)
	{
		if (index < 0 || index > length)
		{
			throw "Index out of range.";
		}

		if (length >= capacity)
		{
			throw "List is full.";
		}

		for (int i = length; i > index; --i)
		{
			data[i] = data[i - 1];
		}
		data[index] = element;
		++length;
	}

	void remove(int index)
	{
		if (index < 0 || index >= length)
		{
			throw "Index out of range.";
		}

		for (int i = index; i < length - 1; ++i)
		{
			data[i] = data[i + 1];
		}
		--length;
	}

	T get(int index)
	{
		if (index < 0 || index >= length)
		{
			throw "Index out of range.";
		}

		return data[index];
	}

	void print()
	{
		for (int i = 0; i < length; ++i)
		{
			std::cout << data[i] << std::endl;
		}
	}

	std::vector<int> search(T searchedData)
	{
		std::vector<int> searched;
		for (int i = 0; i < length; ++i)
		{
			if (data[i] == searchedData)
			{
				searched.emplace_back(i);
			}
		}
		return searched;
	}
};