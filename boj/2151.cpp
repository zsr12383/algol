#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0 ,-1};
int N;
pair<int, int> be[2];
char mp[50][50];
int vst[50][50];

bool isValidPos(int r, int c){
    return r >= 0 && r< N && c>=0 && c< N;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int idx = 0;
    cin >> N;

    for(int i = 0 ; i < N ; i++)
        for(int j = 0 ; j < N ; j++){
            vst[i][j] = 2e9;
            cin >> mp[i][j];
            if(mp[i][j] == '#'){
                be[idx] = {i, j};
                idx++;
            }
        }
    priority_queue<tuple<int, int, int, int>> pq;
    //cost, r, c, prevDir
    pq.push({1, be[0].first, be[0].second, -1});
    vst[be[0].first][be[0].second] = 0;
    while(!pq.empty()){
        int cost = -get<0>(pq.top());
        int r = get<1>(pq.top());
        int c = get<2>(pq.top());
        if(r == be[1].first && c == be[1].second){
            cout << cost << "\n";
            break;
        }
        int prevDir = get<3>(pq.top());
        pq.pop();
        if(cost > vst[r][c]) continue;
        for(int i = 0 ; i < 4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(!isValidPos(nr, nc) || i != prevDir && mp[r][c] == '.' || mp[nr][nc] == '*') continue;
            int ncost = cost;
            ncost += (i != prevDir);
            if(ncost <= vst[nr][nc]) {
                pq.push({-ncost, nr, nc, i});
                vst[nr][nc] = ncost;
            }
        }
    }
}
