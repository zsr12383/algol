#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;

int N, cnt;
vector<int> node[200000];
bool vst[200000];
list<vector<int>> lst;
unordered_map<int, int> mp;

void makeTree2(int n)   //이 삽입 방식이 O(n^2)이어서 시초뜬듯
{
    for (auto it = lst.begin(); it != lst.end();)
    {
        if ((*it)[0] == n)
        {
            node[n].push_back((*it)[1]);
            it = lst.erase(it);
        }
        else if ((*it)[1] == n)
        {
            node[n].push_back((*it)[0]);
            it = lst.erase(it);
        }
        else
            it++;
    }
}

void makeTree()
{
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int n = q.front();
        q.pop();
        makeTree2(n);
        for (auto it : node[n])
            q.push(it);
    }
}

void bfs()
{
    queue<int> q;
    q.push(0);
    int lcnt = 0;
    while (!mp.empty() && !q.empty() && lcnt < q.size())
    {
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
        for (auto it : node[n])
            q.push(it);
    }
}

bool travel()
{
    bfs();
    return N == cnt;
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    N = n;
    bool answer = true;

    for (auto it : path)
        lst.push_back(it);

    makeTree();

    for (auto it : order)
        mp[it[1]] = it[0];

    return travel();
}
