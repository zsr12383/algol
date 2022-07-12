#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int N;
int cost[1000][3];
int dp[1000][3][3];
int home;

int dfs(int now, int color) {
    if (now == N) {
        return 0;
    }

    int& ret = dp[now][color][home];
    if (ret != -1)
        return ret;
    ret = cost[now][color];

    int mn = 1e9;
    for (int i = 0; i < 3; i++) {
        if (color == i) continue;
        if (now == N - 2 && home == i) continue;
        mn = min(mn, dfs(now + 1, i));
    }

    if (mn == 1e9) {
        ret = -1;
        return ret;
    }

    ret += mn;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < 3; j++)
            cin >> cost[i][j];
    memset(dp, -1, sizeof(dp));

    int mn = 1e9;
    for (int i = 0; i < 3; i++) {
        home = i;
        mn = min(mn, dfs(0, i));
    }
    cout << mn <<"\n";
}
