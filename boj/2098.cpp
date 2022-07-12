#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug
#define mymax 987654321

int ans = INT_MAX, N, tmp;
int dp[16][1<<16];
unordered_map<int, int> mp[16];

int travel(int status, int now)
{
    if (status == (1 << N) - 1)
    {
        if (mp[now][0])
            return mp[now][0];
        else
            return mymax;
    }

    int& ret = dp[now][status];
    if (ret != -1) return ret; //이걸 -1로안하고 mymax 로하면 계속 안간곳인줄알고 탐색하게됨

    ret = mymax;
    for (auto it : mp[now])
    {
        int next = it.first;
        if (status & (1 << next)) continue;
        int cost = it.second;
        int cost2 = travel(status | (1 << next), next);
        ret = min(ret, cost2 + cost);
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N;

    memset(dp, -1, sizeof(dp));
    for(int i = 0 ; i < N;i++)
        for (int j = 0; j < N; j++)
        {
            cin >> tmp;
            if (tmp)
                mp[i][j] = tmp;
        }

    cout << travel(1, 0);
}
