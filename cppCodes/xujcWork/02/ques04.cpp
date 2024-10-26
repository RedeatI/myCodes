#include <iostream>
#include <memory>

class student
{
public:
    std::shared_ptr<student> next;
    int id;
    student(int id) : next(nullptr), id(id) {}
};

void work()
{
    int n;
    std::cin >> n;

    std::shared_ptr<student> head = std::make_unique<student>(1);
    std::shared_ptr<student> temp = head;

    for (int i = 2; i <= n; ++i)
    {
        temp->next = std::make_unique<student>(i);
        temp = temp->next;
    }
    temp->next = head;
    temp = head;
    head = nullptr;
    
    int count = 0;
    while(temp->next != temp)
    {
        ++count;
        if (count == 4)
        {
            temp->next = temp->next->next;
            temp = temp->next;
            count = 0;
        }
        else
        {
            temp = temp->next;
        }
    }

    std::cout << temp->id << std::endl;
}

int main()
{
    work();

    return 0;
}