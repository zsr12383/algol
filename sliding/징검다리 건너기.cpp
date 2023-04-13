#include<bits/stdc++.h>
using namespace std;
int solution(vector<int> stones, int k) {
    map<int, int> mp;
    for(int i = 0 ; i < k ; i++)mp[stones[i]]++;
    int answer = mp.rbegin()->first;
    for(int i = k; i < stones.size(); i++){
        mp[stones[i]]++;
        mp[stones[i - k]]--;
        if(mp[stones[i - k]] == 0) mp.erase(stones[i - k]);
        answer = min(mp.rbegin()->first, answer);
    }
    return answer;
}