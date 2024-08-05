#pragma once
#include <string>
#define MAX 50

class myStack
{
public:
    char data[MAX];
    int front = -1;

    // 入栈
    void inStack(char newData);

    // 出栈
    void deStack(std::string &res);

    // 栈是否为空
    bool isStackEmpty();
};

// 优先级比较
bool isPriorityHigher(char first, char second);