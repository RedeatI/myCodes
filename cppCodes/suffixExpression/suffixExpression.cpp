// 中缀表达式转换后缀表达式
//  input: 1+2*(3+4)-5
//  output: 1234+*+5-
#include "Stack.h"
#include "Stack.cpp"
#include <iostream>
using namespace std;

int main()
{
    string t;
    cin >> t;
    myStack Stack;
    string res;

    // 遍历字符串
    for (char it : t)
    {
        // 如果检测到数字，则直接加入到后缀表达式中
        if (it >= 48 && it <= 57)
        {
            res.push_back(it);
        }
        else
        {
            // 若为'('，入栈
            if (it == '(')
            {
                Stack.inStack(it);
            }
            // 若为')'，则依次将栈中的运算符加入后缀表达式，直到出现'('，并从栈中删除'('
            else if (it == ')')
            {
                Stack.deStack(res);
            }
            // 若为其他运算符号
            else
            {
                // 栈空，入栈
                if (Stack.isStackEmpty() == true)
                {
                    Stack.inStack(it);
                }
                // 栈顶元素为'(',入栈
                else if (Stack.data[Stack.front] == '(')
                {
                    Stack.inStack(it);
                }
                // 高于栈顶元素优先级，入栈
                else if (isPriorityHigher(it, Stack.data[Stack.front]) == true)
                {
                    Stack.inStack(it);
                }
                // 否则，依次弹出栈顶运算符，直到一个优先级比它低的运算符或'('为止
                else
                {
                    while (isPriorityHigher(it, Stack.data[Stack.front]) != true && Stack.data[Stack.front] != '(' && Stack.front >= 0)
                    {
                        res.push_back(Stack.data[Stack.front]);
                        Stack.front--;
                    }
                    Stack.inStack(it);
                }
            }
        }
    }

    // 遍历完成，若栈非空，依次弹出栈中所有元素
    if (Stack.isStackEmpty() == false)
    {
        for (int i = Stack.front; i >= 0; i--)
        {
            res.push_back(Stack.data[i]);
        }
    }

    cout << res;

    return 0;
}