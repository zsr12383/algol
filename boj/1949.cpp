#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG
int N;
int people[10001];
vector<int> V[10001];
int dp[10001][2];

int dfs(int curr, bool isGreat, int parent)
{
	int& ret = dp[curr][isGreat];
	if (ret != -1) return ret;
	ret = isGreat ? people[curr] : 0;

	for (auto& nextTown : V[curr])
	{
		if (nextTown == parent) continue;
		int adder = dfs(nextTown, false, curr);
		if (!isGreat) adder = max(adder, dfs(nextTown, true, curr));
		ret += adder;
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int A, B;
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> people[i];
		dp[i][0] = -1;
		dp[i][1] = -1;
	}
	for (int i = 0; i < N - 1; i++)
	{
		cin >> A >> B;
		V[A].push_back(B);
		V[B].push_back(A);
	}
	int ans = max(dfs(1, true, 0), dfs(1, false, 0));
	cout << ans << "\n";
}
