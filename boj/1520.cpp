#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int M, N;
int mp[500][500];
int vst[500][500];
int ans;

bool isValidPos(int r, int c){
    return r>=0 && r<M && c>=0&& c<N;
}

void DFS(int r, int c){
    if(r == M - 1 && c == N - 1) {
        ans++;
        return ;
    }
    for(int i = 0 ; i < 4; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(!isValidPos(nr, nc) || mp[nr][nc] >= mp[r][c] || vst[nr][nc]) continue;
        vst[nr][nc] = 1;
        DFS(nr, nc);
        vst[nr][nc] = 0;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> M >> N;
    for(int i = 0 ; i< M ; i++)
        for(int j = 0 ; j < N;j++)
            cin >> mp[i][j];
    DFS(0, 0);
    cout << ans << "\n";
}
