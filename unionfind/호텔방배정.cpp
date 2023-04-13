#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
unordered_map<long long, long long>par;

long long findParent(long long n){
    if(!par[n]) par[n] = n;
    if(par[n] == n) return n;
    return par[n] = findParent(par[n]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for(auto it: room_number){
        long long pr = findParent(it);
        answer.push_back(pr);
        if(!par[pr + 1]) par[pr + 1] = pr + 1;
        par[pr] = par[pr + 1];
    }
    return answer;
}