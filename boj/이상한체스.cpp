#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int mp[8][8];
int n, m, ans = 987654321;
vector<pair<int, pair<int, int>>> V;
vector<pair<int, int>> V2;

bool isValidPos(int r, int c)
{
    return r >= 0 && r < n&& c >= 0 && c < m;
}

void fillRC(int r, int c, int dir, int val)
{
    r += dr[dir];
    c += dc[dir];
    while (isValidPos(r, c) &&  mp[r][c] != -1)
    {
        mp[r][c] += val;
        r += dr[dir];
        c += dc[dir];
    }
}

void clearRC(int r, int c, int dir, int val)
{
    r += dr[dir];
    c += dc[dir];
    while (isValidPos(r, c) && mp[r][c] != -1)
    {
        mp[r][c] -= val;
        r += dr[dir];
        c += dc[dir];
    }
}

void fillRC2(int r, int c, int dir, int val)
{
    fillRC(r, c, dir, val);
    fillRC(r, c, (dir + 2) % 4, val);
}

void clearRC2(int r, int c, int dir, int val)
{
    clearRC(r, c, dir, val);
    clearRC(r, c, (dir + 2) % 4, val);
}

void fillRC3(int r, int c, int dir, int val)
{
    fillRC(r, c, dir, val);
    fillRC(r, c, (dir + 1) % 4, val);
}

void clearRC3(int r, int c, int dir, int val)
{
    clearRC(r, c, dir, val);
    clearRC(r, c, (dir + 1) % 4, val);
}

void fillRC4(int r, int c, int dir, int val)
{
    fillRC(r, c, dir, val);
    fillRC(r, c, (dir + 1) % 4, val);
    fillRC(r, c, (dir + 2) % 4, val);
}

void clearRC4(int r, int c, int dir, int val)
{
    clearRC(r, c, dir, val);
    clearRC(r, c, (dir + 1) % 4, val);
    clearRC(r, c, (dir + 2) % 4, val);
}
function<void(int, int, int, int)> fillF[] = { fillRC, fillRC2, fillRC3, fillRC4 };
function<void(int, int, int, int)> clearF[] = { clearRC, clearRC2, clearRC3, clearRC4 };

int getEmpty()
{
    int ret = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mp[i][j] == 0)
                ret++;
    return ret;
}

void printmp()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << mp[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void dfs(int lev)
{
    if (lev == V.size())
    {
        int mn = getEmpty();
        if (ans > mn)
        {
            ans = mn;
            //printmp();
        }
        return;
    }
    int r = V[lev].first;
    int c = V[lev].second.first;
    int val = V[lev].second.second;
    for (int i = 0; i < 4; i++)
    {
        fillF[val - 1](r, c, i, val);
        dfs(lev + 1);
        clearF[val - 1](r, c, i, val);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for(int i = 0 ; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> mp[i][j];
            if (mp[i][j] == 6) mp[i][j] = -1;
            else if (mp[i][j] == 5) V2.push_back({ i, j });
            else if (mp[i][j] > 0) V.push_back({ i, {j, mp[i][j]}});
        }
    for(auto it: V2)
        for (int i = 0; i < 4; i++)
            fillRC(it.first, it.second, i, 5);
    dfs(0);
    cout << ans << "\n";
}
