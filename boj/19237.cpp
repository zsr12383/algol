#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int dr[] = { 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, -1, 1 };
int ans;

int N, M, k, sec;
pair<int, int> breezemp[21][21];
int sharkmp[21][21];
map<int, pair<int, pair<int,int>>> shark;

int prior[401][5][5];

void decMp()
{
    for(int i = 1; i<=N;i++)
        for (int j = 1; j <= N; j++)
        {
            if (breezemp[i][j].first)
            {
                breezemp[i][j].second--;
                if (breezemp[i][j].second == 0)
                    breezemp[i][j].first = 0;
            }
        }
}

void breeze()
{
    for (auto it : shark)
        breezemp[it.second.first][it.second.second.first] = { it.first, k };
}

bool isValidPos(int r, int c)
{
    return r > 0 && r <= N && c > 0 && c <= N;
}

int setDir(pair<int, pair<int, pair<int, int>>> shark)
{
    int num = shark.first;
    int r = shark.second.first;
    int c = shark.second.second.first;
    int curDir = shark.second.second.second;

    for (int i = 1; i <= 4; i++)
    {
        int nr = r + dr[prior[num][curDir][i]];
        int nc = c + dc[prior[num][curDir][i]];
        if (isValidPos(nr, nc) && !breezemp[nr][nc].first)
        {
            curDir = prior[num][curDir][i];
            return curDir;
        }
    }

    for (int i = 1; i <= 4; i++)
    {
        int nr = r + dr[prior[num][curDir][i]];
        int nc = c + dc[prior[num][curDir][i]];
        if (isValidPos(nr, nc) && breezemp[nr][nc].first == num)
        {
            curDir = prior[num][curDir][i];
            return curDir;
        }
    }

    return curDir;
};

void move()
{
    //이동조건, 방향 결정, 이동
    vector<int> del;
    for (auto &it : shark)
    {
        sharkmp[it.second.first][it.second.second.first] = 0;

        int dir = setDir(it);
        it.second.first += dr[dir];
        it.second.second.first += dc[dir];
        it.second.second.second = dir;

        int nr = it.second.first;
        int nc = it.second.second.first;

        if (sharkmp[nr][nc])
        {
            if (sharkmp[nr][nc] > it.first)
            {
                del.push_back(sharkmp[nr][nc]);
                sharkmp[nr][nc] = it.first;
            }
            else
                del.push_back(it.first);
        }
        else
            sharkmp[nr][nc] = it.first;
    }
    for (auto it : del)
        shark.erase(it);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M >> k;

    for (int i = 1; i <= N; i++)
        for(int j = 1 ; j <=N;j++)
        {
            int n;
            cin >> n;
            if (n) {
                shark[n] = { i,{j, 0 } };
                sharkmp[i][j] = n;
            }
        }

    for (int i = 1; i <= M; i++)
    {
        int n;
        cin >> n;
        shark[i].second.second = n;
    }

    for (int i = 1; i <= M; i++)
        for (int j = 1; j <= 4; j++)
            for (int l = 1; l <= 4; l++)
                cin >> prior[i][j][l];

    breeze();
    while (ans < 1000)
    {
        move();
        decMp();
        breeze();
        ans++;
        if (shark.size() == 1)
        {
            cout << ans;
            return 0;
        }
    }
    cout << -1;
}
