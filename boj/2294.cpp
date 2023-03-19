#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG
LL dp[10001];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, tmp, cnt = 0;
	cin >> n >> k;
	map<int, bool> V;
	for (int i = 1; i <= k; i++)
		dp[i] = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		if (tmp > k) continue;
		V[tmp] = true;
	}

	for (auto [cost, _] : V)
	{
		for (int j = cost; j <= k; j++)
		{
			dp[j] = min(dp[j], dp[j - cost] + 1);
		}
	}
	cout << (dp[k] != INT_MAX ? dp[k] : -1) << "\n";
}
