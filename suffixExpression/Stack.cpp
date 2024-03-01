#pragma once
#include "Stack.h"
#include <iostream>
using namespace std;

void myStack::inStack(char newData)
{
    front++;
    data[front] = newData;
}

void myStack::deStack(string &res)
{
    while (data[front] != '(' && front >= 0)
    {
        if (data[front] != ')')
        {
            res.push_back(data[front]);
        }
        front--;
    }
    front--;
}

bool myStack::isStackEmpty()
{
    if (front < 0)
        return true;
    else
        return false;
}

bool isPriorityHigher(char first, char second)
{
    if (second == '*' || second == '/' || second == '%')
        return false;
    else if (first == '*' || first == '/' || first == '%')
        return true;
    else
        return false;
}