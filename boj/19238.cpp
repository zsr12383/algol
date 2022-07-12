#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

struct Peopleinfo {
    pair<int, int> start;
    pair<int, int> des;

    Peopleinfo(int r, int c, int dr, int dc) {
        start = { r, c };
        des = { dr, dc };
    }
};

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int N, M, gas;
int mp[22][22], vst[22][22];
pair<int, int> cur;
vector<Peopleinfo> people;

bool isValidPos(int r, int c)
{
    return r > 0 && r <= N && c > 0 && c <= N && !mp[r][c];
}

int bfs(int desr, int desc, bool needchange)
{
    queue<pair<int, pair<int, int>>> q;
    q.push({ cur.first,{cur.second, 0} });
    vst[cur.first][cur.second] = true;

    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second.first;
        int cost = q.front().second.second;
        q.pop();
        if (cost > gas)
        {
            if (needchange)
            {
                cout << "-1";
                exit(0);
            }
            else
                return INT_MAX;
        }
        if (r == desr && c == desc)
        {
            if (needchange) {
                cur.first = r;
                cur.second = c;
            }
            memset(vst, 0, sizeof(vst));
            return cost;
        }
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (isValidPos(nr, nc) && !vst[nr][nc])
            {
                q.push({ nr, {nc, cost + 1} });
                vst[nr][nc] = true;
            }
        }
    }
    if (needchange)
    {
        cout << "-1";
        exit(0);
    }
    return INT_MAX;
}

pair<int, int> findNearPeople()
{
    vector<pair<int, pair<int, pair<int, int>>>> V;
    for (auto i = 0; i < people.size(); i++)
    {
        int dis = bfs(people[i].start.first, people[i].start.second, false);
        V.push_back({ dis, {people[i].start.first, {people[i].start.second, i} } });
    }
    sort(V.begin(), V.end());

    if (V[0].first > gas)
    {
        cout << "-1" << "\n";
        exit(0);
    }

    cur = people[V[0].second.second.second].start;
    gas -= V[0].first;
    auto ret = people[V[0].second.second.second].des;
    people.erase(people.begin() + V[0].second.second.second);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> gas;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> mp[i][j];

    cin >> cur.first >> cur.second;

    for (int i = 0; i < M; i++)
    {
        int startr, startc, desr, desc;
        cin >> startr >> startc >> desr >> desc;
        people.emplace_back(Peopleinfo(startr, startc, desr, desc));
    }

    while (M)
    {
        auto pos = findNearPeople();
        gas += bfs(pos.first, pos.second, true);
        M--;
    }
    cout << gas << "\n";
}