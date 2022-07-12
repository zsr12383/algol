#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

/*
* 4*4 맵
* 
* 물고기 M마리, 상어 1, 마법사1
* 마법사는 물고기와 같은 칸 가능
* 1. 물고기 복제술 저장만 해두고 실제 복제는 x
* 2. 물고기가 한칸씩 이동(상어, 냄새 있는 곳 x, 벗어나는 곳x 이동 가능할 때까지 45도 회전, 이동 불가시 이동 x)
* 3. 상어 연속 3칸 이동(3, 5, 7, 1 vst + dfs가 날듯?, 일반 구현이면 살짝 비효율이 있긴할듯), 상하좌우로, 범위 벗어나면 그리로는 이동 불가, 물고기 있는 칸으로 갈 시 물고기 제외, 제외되는 물고기는 냄새를 남김
* 이 때 이동 방향은 가장 많은 물고기가 제외되는 방향으로, 여러가지 일 경우 사전 순으로 앞서는 방법
* 4. 두단계전 연습에서 생긴 냄새가 사라진다.(life용 맵을 두고 초기값 2로 두면 될듯)
* 5. 복제완료 1에서의 위치와 방향
*/

int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };

unordered_map<char, int> sr = { {'1', -1 }, {'2', 0}, {'3', 1}, {'4', 0} };
unordered_map<char, int> sc = { {'1', 0 }, {'2', -1}, {'3', 0}, {'4', 1} };


int M, S;
int mp[5][5];
unordered_map<int, int> fmp[5][5];
unordered_map<int, int> cpy[5][5];
pair<int, int> cur;
pair < int, pair<string, pair<int, int>>> cand;

bool isValidPos(int r, int c)
{
    return r > 0 && r <= 4 && c > 0 && c <= 4;
}

void copy1()
{
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            cpy[i][j] = fmp[i][j];
}

void copy2()
{
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            for (auto it : cpy[i][j])
                fmp[i][j][it.first] += it.second;
}

void fmove()
{
    //전체 순회하면서 각 칸의 맵 순회하면서 이동 가능한지 조건 검사 후 반대로 이식 해주고 지울 인덱스는 배열로 저장해놨다가 다지움;
    unordered_map<int, int> tmp[5][5];

    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
        {
            for (auto it : fmp[i][j])
            {
                bool cond = false;
                for (int k = 8; k > 0; k--)
                {
                    int dir = (it.first + k) % 8;
                    if (!dir) dir = 8;
                    int nr = i + dr[dir];
                    int nc = j + dc[dir];
                    if (isValidPos(nr, nc) && !(nr == cur.first && nc == cur.second) && !mp[nr][nc])
                    {
                        tmp[nr][nc][dir] += it.second;
                        cond = true;
                        break;
                    }
                }
                if (cond) continue;
                tmp[i][j][it.first] += it.second;
            }
        }

    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            fmp[i][j] = tmp[i][j];
}

int eval2(int r, int c)
{
    int ret = 0;
    for (auto it : fmp[r][c])
        ret += it.second;
    return ret;
}

void dfs(int r, int c, int eat, string rout, vector<pair<int, int>>V)
{
    if (rout.size() == 3)
    {
        if (eat > cand.first)
            cand = { eat,{ rout,{ r, c } } };
        else if (eat == cand.first)
            if(rout < cand.second.first)
                cand = { eat, { rout,{ r, c } } };
        return;
    }
    for(char i = '1'; i <= '4'; i++)
    {
        int nr = r + sr[i];
        int nc = c + sc[i];
        int sum = 0;
        if (!isValidPos(nr, nc)) continue; //왔던 곳도 가도 되나? 됨, 사실 됨이 아니라 되어야만 맞음
        if(find(V.begin(), V.end(), make_pair(nr, nc)) == V.end())
            sum = eval2(nr, nc);
     
        V.push_back({nr, nc});
        dfs(nr, nc, eat + sum, rout + i, V);
        V.pop_back();
    }
}

void smove()
{
    cand = { 0, {"999", {0, 0}} };
    dfs(cur.first, cur.second, 0, "", {});
    for (auto it : cand.second.first)
    {
        cur.first += sr[it];
        cur.second += sc[it];
        if (fmp[cur.first][cur.second].size())
        {
            fmp[cur.first][cur.second].clear();
            mp[cur.first][cur.second] = 3;
        }
    }
    // rout 경로 별로가면서 실제 물고기들 죽이기, 향기 3 남기기
}

void breeze()
{
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (mp[i][j])
                mp[i][j]--;
}

int eval()
{
    int ret = 0;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            ret += eval2(i, j);
    return ret;
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> M >> S;

    for (int i = 0; i < M; i++)
    {
        int r, c, d;
        cin >> r >> c >> d;
        fmp[r][c][d]++;
    }
    cin >> cur.first >> cur.second;

    while (S--)
    {
        copy1();
        fmove();
        smove();
        breeze();
        copy2();
    }
    cout << eval();
}
