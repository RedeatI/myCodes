#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int txor = 0;
        int num;
        int num1[32] = {0}, num2[32] = {0};
        for (int i = 0; i < n; ++i)
        {
            cin >> num;
            txor ^= num;
            for (int bit = 0; bit < 32; ++bit)
            {
                if (num & (1 << bit))
                {
                    num1[bit] ^= num;
                }
                else
                {
                    num2[bit] ^= num;
                }
            }
        }
        int bit = 1;
        int bitcount = 0;
        while (!(txor & bit))
        {
            bit <<= 1;
            bitcount++;
        }
        if (num1[bitcount] > num2[bitcount])
        {
            swap(num1[bitcount], num2[bitcount]);
        }
        cout << num1[bitcount] << " " << num2[bitcount] << endl;
    }
    return 0;
}