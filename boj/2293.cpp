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
	vector<int> V(100);
	for(int i = 0 ; i < n; i++)
	{
		cin >> tmp;
		if (tmp > k) continue;
		V[cnt] = tmp;
		cnt++;
	}
	V.resize(cnt);
	dp[0] = 1;
	for(int i = 0 ; i < cnt ; i++)
		for(int j = V[i] ; j <= k ; j++)
		{
			dp[j] += dp[j - V[i]];
		}
	cout << dp[k] << "\n";
}
