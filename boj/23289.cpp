#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

/*
* ��ǳ�� �迭(��ǳ�� �ʿ� ����: ��ǥ, ����)
* 0 ��ĭ 1~4 ����
* ��ǳ�� �ٶ� -> �µ� ���� -> �ٱ� �µ� 1���� -> ���ݸ� ���� -> �����ϴ� ��� ĭ �µ� K �̻� �� ���� �ƴ� �� �ݺ�
* �µ� ���� ��ƾ�� BFS ����Ʈ üũ�� ó���ؾ��ҵ�(�� ���� �˻��ϸ鼭, �� ��ǳ�� ���� ������ ���)
* ���� ��ǳ�Ⳣ���� �ߺ� ���� x(��ǳ�� �迭 �ʿ�, ��ǥ�� ���� �ʿ��ҵ�)
* �µ� ���� �Ŀ� �µ��� ��������, ������ ���� ��ȭ�� ������ ��ġ�� �ȵǹǷ� �ӽù迭���� �ű⿡ �����ϴ� �������(���� �������� 1/4�� ����, ���̳� invalid�� ������ �� �����ϰ� �װ���ŭ ������ġ����)
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
