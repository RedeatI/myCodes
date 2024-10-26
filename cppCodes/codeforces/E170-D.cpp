// n:清单中的记录数量, m:在游戏中将获得的总点数
// r[i] = 0:获取一个属性点
// r[i] > 0:智力检查
// r[i] < 0:力量检查
// 打印一个整数——你可以通过的最大检查数量。

#include <bits/stdc++.h>
using namespace std;

void work()
{
    int n, m;
    cin >> n >> m;
    vector<int> r(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> r[i];
    }

    r.push_back(0);        // 在记录末尾添加一个 0，表示获取一个属性点
    vector<int> f(m + 10); // 辅助差分数组 f，用于记录属性点的分配情况
    vector<int> dp(m + 1); // 动态规划数组 dp，用于记录通过检查的最大数量
    int s = 0;             // 记录当前已分配的智力属性数量

    for (int i = 1; i < r.size(); i++)
    {
        int x = r[i];
        if (x < 0) // 如果是力量检查
        {
            x = -x;     // 取绝对值
            if (x <= s) // 如果当前力量点数足够通过检查
            {
                f[x]++; // 表示从位置 x 开始，所有元素增加 1。
            }
        }
        else if (x > 0) // 如果是智力检查
        {
            x = s - x;  // 计算当前智力点数是否足够通过检查
            if (x >= 0) // 如果当前智力点数足够通过检查
            {
                f[0]++;     // 表示从位置 0 开始，所有元素增加 1。
                f[x + 1]--; // 表示从位置 x + 1 开始，所有元素减少 1。
            }
        }
        else // 如果是获取一个属性点
        {
            for (int i = 1; i <= m; i++)
            {
                f[i] += f[i - 1]; // 累加 f 数组，计算当前属性点分配情况
            }
            for (int i = 0; i <= m; i++)
            {
                dp[i] += f[i]; // 更新 dp 数组，记录通过检查的最大数量
            }
            for (int i = m; i >= 1; i--)
            {
                dp[i] = max(dp[i - 1], dp[i]); // 计算当前最大通过检查数量
            }
            for (int i = 0; i <= m; i++)
            {
                f[i] = 0; // 重置 f 数组
            }
            s++; // 增加已分配的属性点数量
        }
    }

    int ans = 0;
    for (auto x : dp)
    {
        ans = max(ans, x); // 找到 dp 数组中的最大值，即最大通过检查数量
    }
    cout << ans << '\n'; // 输出结果
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int _ = 1;
    // cin >> _;
    while (_--)
    {
        work();
    }

    return 0;
}