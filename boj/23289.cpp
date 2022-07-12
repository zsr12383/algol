#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

/*
* 온풍기 배열(온풍기 필요 정보: 좌표, 방향)
* 0 빈칸 1~4 방향
* 온풍기 바람 -> 온도 조절 -> 바깥 온도 1감소 -> 초콜릿 섭취 -> 조사하는 모든 칸 온도 K 이상 시 종료 아닐 시 반복
* 온도 증가 루틴은 BFS 비지트 체크로 처리해야할듯(벽 조건 검사하면서, 한 온풍기 끝날 때마다 멤셋)
* 같은 온풍기끼리는 중복 증가 x(온풍기 배열 필요, 좌표와 방향 필요할듯)
* 온도 증가 후엔 온도가 퍼져야함, 증가에 따른 변화가 영향을 미치면 안되므로 임시배열만들어서 거기에 대입하는 방식으로(인접 방향으로 1/4씩 증가, 벽이나 invalid로 못가는 곳 제외하고 그값만큼 원래위치빼줌)
*/

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int R, C, K, W, ans;
int mp[21][21];
int tmp[21][21];
int wall[21][21][4];
vector < pair<int, pair<int, int>>> wind;
vector<pair<int, int>> target;

bool isValidPos(int r, int c)
{
    return r >= 1 && r <= R && c > 0 && c <= C;
}

void sumNmemset()
{
    for(int i = 1 ; i<=R;i++)
        for (int j = 1; j <= C; j++)
        {
            mp[i][j] += tmp[i][j];
            tmp[i][j] = 0;
        }
}

void blow()
{
    for (auto it : wind)
    {
        int dir = it.first;
        queue<pair<int,pair<int, int>>> q;
        q.push({ 5, {it.second.first + dr[dir], it.second.second + dc[dir]}});
        tmp[it.second.first + dr[dir]][it.second.second + dc[dir]] = 5;
        while (!q.empty())
        {
            int add = q.front().first;
            int r = q.front().second.first;
            int c = q.front().second.second;
            q.pop();

            int nr = r + dr[dir];
            int nc = c + dc[dir];
            add--;
            if (add && isValidPos(nr, nc))
            {
                if (!tmp[nr][nc] && !wall[r][c][dir]) {
                    tmp[nr][nc] = add;
                    q.push({ add, {nr, nc} });
                }

                for (int i = 1; i <= 3; i += 2)
                {
                    int tmpdir = (dir + i) % 4;
                    int tmpnr = nr + dr[tmpdir];
                    int tmpnc = nc + dc[tmpdir];
                    if (isValidPos(tmpnr, tmpnc) && !tmp[tmpnr][tmpnc] && !wall[r][c][tmpdir] && !wall[r + dr[tmpdir]][c + dc[tmpdir]][dir])
                    {
                        tmp[tmpnr][tmpnc] = add;
                        q.push({ add, {tmpnr, tmpnc} });
                    }
                }
            }
        }
        sumNmemset();
    }
}

void spread()
{
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
        {
            int N = mp[i][j];
            for (int k = 0; k < 4; k++)
            {
                int nr = i + dr[k];
                int nc = j + dc[k];
                if (isValidPos(nr, nc) && !wall[i][j][k] && mp[i][j] > mp[nr][nc])
                {
                    tmp[nr][nc] += (mp[i][j] - mp[nr][nc]) / 4;
                    N -= (mp[i][j] - mp[nr][nc]) / 4;
                }
            }
            tmp[i][j] += N;
        }
    memset(mp, 0, sizeof(mp));
    sumNmemset();
}

void dec()
{
    for(int i = 1;i<=R;i++)
        for (int j = 1; j <= C; j++)
        {
            if (i > 1 && i < R && j > 1 && j < C) continue;
            if (mp[i][j]) mp[i][j]--;
        }
}

bool check()
{
    for (auto it : target)
        if (mp[it.first][it.second] < K)
            return true;
    return false;
}

int trans(int num)
{
    switch (num)
    {
    case 1:
        return 1;
    case 2:
        return 3;
    case 3:
        return 0;
    case 4:
        return 2;
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> R >> C >> K;
    for (int i = 1; i <= R; i++)
        for (int j = 1; j <= C; j++)
        {
            cin >> mp[i][j];
            if (!mp[i][j]) continue;
            if (mp[i][j] < 5)
                wind.push_back({trans(mp[i][j]), {i, j}});
            else if (mp[i][j] == 5)
                target.push_back({i, j});
            mp[i][j] = 0;
        }
    cin >> W;
    for (int i = 1; i <= W; i++)
    {
        int x, y, t;
        cin >> x >> y >> t;
        wall[x][y][t] = 1;
        if(isValidPos(x + dr[t], y + dc[t]))
            wall[x + dr[t]][y + dc[t]][(t + 2) % 4] = 1;
    }

    while (check() && ans < 101)
    {
        blow();
        spread();
        dec();
        ans++;
    }
    cout << ans;
}
