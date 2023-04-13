#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) {
    vector<vector<int>> answer;
    deque<int> r, l;
    int rSiz = rc.size();
    int cSiz = rc[0].size();
    deque<deque<int>> mid(rSiz, deque<int>(cSiz - 2));
    int idx = 0;
    for(auto &it : rc){
        l.push_back(it[0]);
        r.push_front(it.back());
        for(int i = 1; i < cSiz -1 ; i++)
           mid[idx][i - 1] = it[i];
        idx++;
    }
    
    for(auto &it : operations){
        if(it[0] == 'R'){
            mid[0].push_front(l[0]);
            l.pop_front();
            r.push_back(mid[0].back());
            mid[0].pop_back();
            mid.back().push_back(r[0]);
            r.pop_front();
            l.push_back(mid.back()[0]);
            mid.back().pop_front();
            continue;
        }
        l.push_front(l.back());
        l.pop_back();
        r.push_back(r[0]);
        r.pop_front();
        mid.emplace_front(move(mid.back()));
        mid.pop_back();
    }
    
    answer.resize(rSiz, vector<int>(cSiz, 0));
    for(int i = 0 ; i < rSiz ; i++){
        answer[i][0] = l[i];
        answer[rSiz - 1 - i].back() = r[i];
        for(int j = 1; j < cSiz - 1; j++){
            answer[i][j] = mid[i][j - 1];       
        }
    }
    return answer;
}