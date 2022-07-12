#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int N, M, K;
vector<string> board;
string target;

int dp[100][100][80];
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

bool isValidPos(int r, int c) {
    return r >= 0 && r < N&& c >= 0 && c < M;
}

int dfs(int r, int c, int lev)
{
    if (target[lev] != board[r][c]) return 0;
    if (lev == target.length() - 1)
        return 1;
    int& ret = dp[r][c][lev];
    if (ret != -1)
        return ret;
    //cout << r << " " << c << "\n";
    ret = 0;

    for(int i = 0 ; i < 4;i++)
        for (int j = 1; j <= K; j++) {
            int nr = r + j * dr[i];
            int nc = c + j * dc[i];
            if (!isValidPos(nr, nc)) continue;
            ret += dfs(nr, nc, lev + 1);
        }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        string S;
        cin >> S;
        board.push_back(S);
    }
    cin >> target;
    memset(dp, -1, sizeof(dp));

    int sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            sum += dfs(i, j, 0);
    cout << sum << "\n";
}
