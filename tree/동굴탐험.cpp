#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
unordered_map<int, vector<int>> key;
vector<int> node[200000];
vector<int> tree[200000];
bool vst[200000];

void makeTree()
{
    queue<int> q;
    q.push(0);
    while(!q.empty())
    {
        int curr = q.front();
        q.pop();
        vst[curr] = true;
        for(auto next : node[curr]){
            if(vst[next]) continue;
            q.push(next);
            tree[curr].push_back(next);
            key[next].push_back(curr);
        }
    }
}

bool isPossiblePos(int n){
    for(auto precond : key[n])
        if(!vst[precond]) return false;
    return true;
}

bool bfs(int n)
{
    if(!isPossiblePos(0)) return false;
    int cnt = 0;
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        if(vst[curr]) continue;
        if(++cnt == n) return true;
        vst[curr] = true;
        for(auto next : tree[curr]){
            if(isPossiblePos(next)) q.push(next);
        }
    }
    return false;
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    for (auto it : path){
        node[it[0]].push_back(it[1]);
        node[it[1]].push_back(it[0]);
    }
    makeTree();
    memset(vst, 0, sizeof(bool) * n);
    for (auto it : order){
        key[it[1]].push_back(it[0]);
        tree[it[0]].push_back(it[1]);
    }    
    return bfs(n);
}
