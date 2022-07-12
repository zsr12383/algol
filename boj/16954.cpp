#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int mp[8][8];

int dr[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int dc[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

bool isValidPos(int r, int c)
{
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}
//(7, 0), ( 0, 7)
int moveWall()
{
    int ret = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 7; j >=0; j--)
        {
            if (!mp[j][i]) continue;
            mp[j][i] = 0;
            if (j < 7) {
                mp[j + 1][i] = 1;
                ret++;
            }
        }
    return ret;
}

bool moveCharacter()
{
    queue<pair<int, pair<int, int>>> q;
    q.push({ 7, {0, 0} });
    int lev = 0;
    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second.first;
        int lv = q.front().second.second;
        q.pop();

        if (r == 0 && c == 7) return true;
        if (lev > 16) return false;
        if (lev != lv) {
            lev = lv;
            if (!moveWall())
                return true;
        }
        if (mp[r][c]) continue;

        for (int i = 0; i < 8; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (isValidPos(nr, nc) && !mp[nr][nc])
            {
                q.push({ nr, {nc, lv + 1} });
            }
        }
        q.push({ r, {c, lv + 1} });
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string str;
    for (int i = 0; i < 8; i++)
    {
        cin >> str;
        for (int j = 0; j < 8; j++)
            if(str[j] == '#')
                mp[i][j] = 1;
    }
    
    cout << moveCharacter();

    return 0;
}
