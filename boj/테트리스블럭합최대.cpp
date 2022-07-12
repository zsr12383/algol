#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int n, m, ans;
int mp[200][200];
bool vst[200][200];

bool isValidPos(int r, int c)
{
    return r >= 0 && r < n&& c >= 0 && c < m;
}

void dfs(int r, int c, int lev, int sum)
{
    if (lev == 4)
    {
        ans = max(ans, sum);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (!isValidPos(r, c) || vst[nr][nc]) continue;
        vst[nr][nc] = true;
        dfs(nr, nc, lev + 1, sum + mp[r][c]);
        vst[nr][nc] = false;
    }
}

void shapeH(int r, int c)
{
    vector<int> V;
    int sum = mp[r][c];
    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (!isValidPos(nr, nc)) continue;
        V.push_back(i);
        sum += mp[nr][nc];
    }
    if (V.size() < 3) return;
    if (V.size() == 3) {
        ans = max(sum, ans);
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        ans = max(ans, sum - mp[nr][nc]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mp[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            vst[i][j] = true;
            dfs(i, j, 0, 0);
            vst[i][j] = false;
            shapeH(i, j);
        }
    cout << ans << "\n";
}
