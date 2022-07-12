#include <bits/stdc++.h>
using namespace std;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int mp[20][20];
int train[20][20];
int vst[20][20];
int n, m, k;
long long ans;

bool isValidPos(int r, int c)
{
    return r >=0 && r<n && c>=0 && c<n;
}

struct Train {
    deque<pair<int,int>> elem;

    void trans(){
        reverse(elem.begin(), elem.end());
        int val = 1;
        for(auto it : elem)
            mp[it.first][it.second] = val++;
    }

    void move(){
        int r = elem[0].first;
        int c = elem[0].second;
        int idx = train[r][c];
        for(int i = 0; i <4;i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(isValidPos(nr, nc) && (mp[nr][nc] == -1 || mp[nr][nc] == mp[elem.back().first][elem.back().second])) {
                elem.push_front({nr, nc});
                train[nr][nc] = idx;
            }
        }
        r = elem.back().first;
        c = elem.back().second;
        mp[r][c] = -1;
        train[r][c] = -1;
        elem.pop_back();
        int val = 1;
        for(auto it : elem) {
            train[it.first][it.second] = idx;
            mp[it.first][it.second] = val++;
        }
    }
};

Train t[6];

void bfs(int r, int c, int idx)
{
    t[idx] = Train();
    vst[r][c] = true;
    queue<pair<int, int>> q;
    q.push({r, c});
    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        t[idx].elem.push_back({row, col});
        q.pop();
        for(int i = 0 ; i<4;i++)
        {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(isValidPos(nr, nc) && !vst[nr][nc] && mp[nr][nc] > 0) {
                if (mp[row][col] == 1 && mp[nr][nc] == 3) continue;
                vst[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    int val = 1;
    for(auto it : t[idx].elem) {
        train[it.first][it.second] = idx;
        mp[it.first][it.second] = val++;
    }
}

void getTrain()
{
    int idx = 1;
    for(int i = 0 ; i<n;i++)
        for(int j = 0 ;j<n;j++) {
            if(mp[i][j] != 1) continue;
            bfs(i, j, idx++);
        }
}

int nnr[] = {0, -1,0, 1};
int nnc[] = {1,0,-1,0};

void arrow(int round)
{
    int dir = (round / n) % 4;
    round %= n;
    int ir[] = {round, n -1, n - 1 - round, 0};
    int ic[] = {0, round, n - 1, n - 1 - round};
    int r = ir[dir];
    int c = ic[dir];
    for(int i = 0; i<n;i++)
    {
        if(mp[r][c] > 0)
        {
            ans += mp[r][c] * mp[r][c];
            t[train[r][c]].trans();
            break;
        }
        r += nnr[dir];
        c += nnc[dir];
    }
}

int main() {

    cin >> n >> m >> k;

    for(int i = 0 ; i<n;i++)
        for(int j = 0 ;j<n;j++) {
            cin >> mp[i][j];
            if(mp[i][j] == 4)
                mp[i][j] = -1;
        }

    getTrain();

    for(int i = 0 ; i < k ; i++)
    {
        for(int j = 1 ; j <= m ; j++)
            t[j].move();
        arrow(i);
    }
    cout << ans << "\n";
    return 0;
}
