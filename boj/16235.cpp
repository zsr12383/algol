#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

int N, M, K;

deque<int>tree[10][10];
int mp[10][10];
int nut[10][10];
map<pair<int, int>, int> death;

int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void spring()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < tree[i][j].size(); k++)
            {
                if (tree[i][j][k] > mp[i][j])
                {
                    M -= (int)tree[i][j].size() - k;
                    for (; k < tree[i][j].size(); k++)
                        death[{i, j}] += tree[i][j][k] / 2; // 양분을 다 추가하고 버리는 거야 아니면 버리는 거야?
                    tree[i][j].resize(k - 1); // 리사이즈 값 보존하며 잘되는지 확인
                    break;
                }
                mp[i][j] -= tree[i][j][k];
                tree[i][j][k]++;
            }
        }
}

void summer()
{
    for (auto it : death)
        mp[it.first.first][it.first.second] += it.second;
    death.clear();
}

bool isValid(int r, int c)
{
    return r >= 0 && r < N&& c >= 0 && c < N;
}

void fall()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (tree[i][j].empty()) continue;
            for (int k = 0; k < 8; k++)
            {
                int nr = i + dr[k];
                int nc = j + dc[k];
                if (!isValid(nr, nc)) continue;
                for (auto it : tree[i][j])
                    if (it && it % 5 == 0)
                    {
                        tree[nr][nc].push_front(1);
                        M++;
                    }
            }
        }
}

void winter()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mp[i][j] += nut[i][j];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> K;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> nut[i][j];
            mp[i][j] = 5;
        }

    for (int i = 0; i < M; i++)
    {
        int r, c, age;
        cin >> r >> c >> age;
        tree[r - 1][c - 1].push_back(age);
    }

    for (int i = 0; i < K; i++)
    {
        spring();
        summer();
        fall();
        winter();
    }

    cout << M;
}
