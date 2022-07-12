#include<queue>
#include<iostream>
#include<unordered_map>
using namespace std;

int N, cnt;
vector<int> node[200000];
vector<int> node2[200000];
bool vst[200000];
list<vector<int>> lst;
unordered_map<int, int> mp;

void makeTree()
{
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int n = q.front();
        q.pop();
        vst[n] = true;
        for (auto it : node[n])
        {
            if (vst[it]) continue;
            node2[n].push_back(it);
            q.push(it);
        }
    }
}

void bfs()
{
    queue<int> q;
    q.push(0);
    int lcnt = 0;
    while (!q.empty() && lcnt < q.size())
    {
        if (mp.empty()) {
            N = cnt;
            return;
        }
        int n = q.front();
        q.pop();
        if (mp[n] && !vst[mp[n]]) {
            q.push(n);
            lcnt++;
            continue;
        }
        lcnt = 0;
        if (mp[n])
            mp.erase(n);
        vst[n] = true;
        cnt++;
        for (auto it : node2[n])
            q.push(it);
    }
}

bool travel()
{
    memset(vst, 0, sizeof(vst));
    bfs();
    return N == cnt;
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    N = n;
    bool answer = true;

    for (auto it : path)
    {
        node[it[0]].push_back(it[1]);
        node[it[1]].push_back(it[0]);
    }

    makeTree();

    for (auto it : order)
        mp[it[1]] = it[0];

    return travel();
}

int main()
{
    solution(9, { {0, 1}, {0, 3}, {0, 7}, {8, 1}, {3, 6}, {1, 2}, {4, 7}, {7, 5} }, { {8, 5}, {6, 7}, {4, 1} });
}