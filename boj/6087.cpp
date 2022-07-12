#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int W, H;

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

char mp[100][100];
int vst[100][100];
pair<int, int> cur;

bool isValidPos(int r, int c)
{
    return r >= 0 && r < H&& c >= 0 && c < W;
}

int bfs()
{
    queue<pair<int, pair<int, pair<int, pair<int, int>>>>> q;
    q.push({ cur.first, {cur.second, {-1, {0, -1}}}});
    mp[cur.first][cur.second] = '*';
    int ans = INT_MAX;
    while (!q.empty())
    {
        int a = q.size();
        auto tmp = q.front();
        int r = tmp.first;
        int c = tmp.second.first;
        int cnt = tmp.second.second.first;
        int cost = tmp.second.second.second.first;
        int prevdir = tmp.second.second.second.second;
        q.pop();

        if (mp[r][c] == 'C') {
            ans = min(ans, vst[r][c]);
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (isValidPos(nr, nc) && mp[nr][nc] != '*')
            {
                if (prevdir != i && vst[nr][nc] >= cnt + 1)
                {
                    q.push({ nr,{nc, {cnt + 1, {cost + 1, i}}} });
                    vst[nr][nc] = cnt + 1;
                }
                else if (prevdir == i && vst[nr][nc] >= cnt)
                {
                    vst[nr][nc] = cnt;
                    q.push({ nr,{nc, {cnt, {cost + 1, i}}} });
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> W >> H;

    for (int i = 0; i < H; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < W; j++)
        {
            mp[i][j] = tmp[j];
            vst[i][j] = INT_MAX;
            if (tmp[j] == 'C')
            {
                cur.first = i;
                cur.second = j;
            }
        }
    }
    cout << bfs();
}
