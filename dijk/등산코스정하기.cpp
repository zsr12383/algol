#include<bits/stdc++.h>
using namespace std;
vector<int> answer = {INT_MAX, INT_MAX};
map<int, bool> mp;
map<int, int> grp[50001];
int dist[50001];

void dijk(int start){
    priority_queue<pair<int, int>> pq;
    pq.push({start, 0});
    dist[start] = INT_MAX;
    while(!pq.empty()){
        auto curr = pq.top();
        pq.pop();
        if(dist[curr.first] < curr.second){
            continue;
        }
        if(mp[curr.first]==true){
            if(answer[1] < curr.second){
               continue;
            }
            if(answer[1] == curr.second){
                answer = answer[0] > curr.first ? vector<int> {curr.first, curr.second} : answer;
                continue;
            }
            if(answer[1] > curr.second){
                answer = {curr.first, curr.second};
                continue;
            }
        }
        for(auto it: grp[curr.first]){
            int mx = max(it.second, curr.second);
            if(dist[it.first] == -1 || dist[it.first] !=-1 && mx< dist[it.first]){
                dist[it.first] = mx;
                pq.push({it.first, mx});
            }
        }
    }
    dist[start] = 0;
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    for(auto it : summits){
        mp[it]= true;
    }
    for(auto it : paths){
        grp[it[0]][it[1]] = it[2];
        grp[it[1]][it[0]] = it[2];
    }
    memset(dist, -1, sizeof(dist));
    for(auto it : gates) {
        dijk(it);
    }
    
    return answer;
}