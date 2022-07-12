#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int N, sec;
int mp[20][20];
bool vst[20][20];
vector<pair<int, pair<int, int>>> feed;
int siz = 2;
int needEvolve = 2;
pair<int, int> cur;
// 먹으면 그지형 없애고 먹이에서 빼는 것도

int dr[] = { -1, 0, 1,0 };
int dc[] = { 0, 1,0,-1 };

bool isValidPos(int r, int c) {
    return r >= 0 && r < N&& c >= 0 && c < N && !vst[r][c];
}

int bfs(int desr, int desc)
{
    queue<pair<int, pair<int, int>>> q;
    q.push({ cur.first ,{cur.second, 0} });
    memset(vst, 0, sizeof(vst));

    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second.first;
        int cost = q.front().second.second;
        q.pop();
        if (r == desr && c == desc) return cost;
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (isValidPos(nr, nc) && mp[nr][nc] <= siz )
            {
                vst[nr][nc] = true;
                q.push({ nr, {nc,cost + 1} });
            }
        }
    }
    return INT_MAX;
}

void hunt()
{
    while (!feed.empty())
    {
        vector<pair<int, pair<int, pair<int, int>>>> V;
        for (int i = 0; i < feed.size(); i++)
        {
            if (feed[i].first >= siz)  continue;
            int dis = bfs(feed[i].second.first, feed[i].second.second);
            if(dis <INT_MAX)
                V.push_back({ dis, {feed[i].second.first, {feed[i].second.second, i}} });
        }
        if (V.empty()) return;
        sort(V.begin(), V.end());

        sec += V[0].first;
        needEvolve--;
        mp[V[0].second.first][V[0].second.second.first] = 0;
        feed.erase(feed.begin() + V[0].second.second.second);
        if (!needEvolve)
        {
            siz++;
            needEvolve = siz;
        }
        cur = {V[0].second.first, V[0].second.second.first};
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            cin >> mp[i][j];
            if (mp[i][j] == 9)
            {
                cur = { i, j };
                mp[i][j] = 0;
            }
            else if (mp[i][j])
                feed.push_back({ mp[i][j],{i, j} });
        }

    hunt();

    cout << sec;
}
