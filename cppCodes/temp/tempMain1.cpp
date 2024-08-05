#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int logi(int a, int b)
{
	int t = 0;
	ll v = 1;
	while (v < b)
	{
		v *= a;
		++t;
	}
	return t;
}

void work()
{
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}

	int t = 0;
	ll ans = 0;

	for (int i = 1; i < n; ++i)
	{
		if (a[i - 1] > 1 && a[i] == 1)
		{
			cout << "-1\n";
			return;
		}
		else
		{
			int l = logi(a[i], a[i - 1]);
			l = (l == 0 ? 0 : __lg(2 * l - 1));
			t = max(0, t + l);
			ans += t;
		}
	}

	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int _ = 1;
	cin >> _;
	while (_--)
	{
		work();
	}

	return 0;
}