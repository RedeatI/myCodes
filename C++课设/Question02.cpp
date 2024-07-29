// 2886 11.9%
/*
23-24(2)第4次线上赛
2886：二进制高手
时间限制：1 S   /  内存限制：65536 KB
AC：23   /  Submit：193

描述
罗少是二进制高手，他非常喜欢2的非负整数次幂，例如：1,2,4,8...
这天，罗少恰好在研究32位无符号型整数unsigned int
他发现对于任意一个32位无符号型整数n总是可以通过若干次加2操作变成2的非负整数次幂！
现在，给你一个非负整数n，请你编程计算一下至少需要加几次2才能变成2的非负整数次幂。

输入
第一行是一个正整数T表示测试案例的数量。
每组案例包含一个unsigned int类型的数字

输出
针对每组案例，在一行中输出n至少需要加几次2才能变成2的非负整数次幂。

提示说明
思考 C++ 中 unsigned int 的溢出现象
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        unsigned n;
        cin >> n;
        if (n == 1)
        {
            cout << 0 << endl;
            continue;
        }
        else if (n == 0)
        {
            cout << 1 << endl;
            continue;
        }
        long long temp = 1;
        if (n & 1)
        {
            cout << (4294967295 - n) / 2 + 1 << endl;
            continue;
        }
        while (temp < n)
        {
            temp <<= 1;
        }
        if (temp == 4294967296)
        {
            cout << (temp - n) / 2 + 1 << endl;
        }
        else
        {
            cout << (temp - n) / 2 << endl;
        }
    }
    return 0;
}