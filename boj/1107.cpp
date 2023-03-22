#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG
int N, M;
set<int> S{ 0,1,2,3,4,5,6,7,8,9 };
int vst[500001];
int ans;
int strCnt;

void dfs(int lev, int number)
{
	if(lev == strCnt + 1)
	{
		ans = min(ans, abs(N - number) + lev);
		return;
	}

	for(auto num : S)
	{
		dfs(lev + 1, number * 10 + num);
	}
	ans = min(ans, abs(N - number) + lev);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> N >> M;
	int tmp;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		S.erase(tmp);
	}
	ans = abs(N - 100);
	strCnt = to_string(N).size();
	for(auto num : S)
		dfs(1, num);
	cout << ans << "\n";
}
