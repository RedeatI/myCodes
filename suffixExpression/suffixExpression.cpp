// 中缀表达式转换后缀表达式
//  input: 1+2*(3+4)-5
//  output: 1234+*+5-
#include <bits/stdc++.h>
using namespace std;

constexpr auto MAX = 50;

class Stack
{
public:
    char data[MAX];
    int front = -1;

    // 入栈
    void inStack(char newData)
    {
        front++;
        data[front] = newData;
    }

    // 出栈
    void deStack(string &res)
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

    // 栈是否为空
    bool isStackEmpty()
    {
        if (front < 0)
            return true;
        else
            return false;
    }
};

// 优先级比较
bool isPriorityHigher(char first, char second)
{
    if (second == '*' || second == '/' || second == '%')
        return false;
    else if (first == '*' || first == '/' || first == '%')
        return true;
    else
        return false;
}

int main()
{
    string t;
    cin >> t;
    Stack stack;
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
                stack.inStack(it);
            }
            // 若为')'，则依次将栈中的运算符加入后缀表达式，直到出现'('，并从栈中删除'('
            else if (it == ')')
            {
                stack.deStack(res);
            }
            // 若为其他运算符号
            else
            {
                // 栈空，入栈
                if (stack.isStackEmpty() == true)
                {
                    stack.inStack(it);
                }
                // 栈顶元素为'(',入栈
                else if (stack.data[stack.front] == '(')
                {
                    stack.inStack(it);
                }
                // 高于栈顶元素优先级，入栈
                else if (isPriorityHigher(it, stack.data[stack.front]) == true)
                {
                    stack.inStack(it);
                }
                // 否则，依次弹出栈顶运算符，直到一个优先级比它低的运算符或'('为止
                else
                {
                    while (isPriorityHigher(it, stack.data[stack.front]) != true && stack.data[stack.front] != '(' && stack.front >= 0)
                    {
                        res.push_back(stack.data[stack.front]);
                        stack.front--;
                    }
                    stack.inStack(it);
                }
            }
        }
    }

    // 遍历完成，若栈非空，依次弹出栈中所有元素
    if (stack.isStackEmpty() == false)
    {
        for (int i = stack.front; i >= 0; i--)
        {
            res.push_back(stack.data[i]);
        }
    }

    cout << res;

    return 0;
}