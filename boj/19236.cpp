#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int answer;

void DFS(pair<int, int> sharkPos, int sharkDir, vector<pair<int, int>> fishLocate, vector<int> fishDirect, map<pair<int, int>, int> mp, short flg, int ans);

bool isValidPos(int r, int c)
{
    return r >= 0 && r < 4 && c >= 0 && c < 4;
}

bool canFishMove(int r, int c, pair<int, int> sharkPos)
{
    return isValidPos(r, c) && (r != sharkPos.first || c != sharkPos.second);
}

void fishMove(pair<int, int> &sharkPos, vector<pair<int, int>>& fishLocate, vector<int>& fishDirect, map<pair<int, int>, int> &mp, short &flg)
{
    int i = 1;
    int idx = 0;
    int lmt = 1 << 16;
    while (i != lmt)
    {
        if (i & flg)
        {
            for (int j = 0; j < 8; j++)
            {
                int nr = fishLocate[idx].first + dr[(fishDirect[idx] + j) % 8];
                int nc = fishLocate[idx].second + dc[(fishDirect[idx] + j) % 8];
                if (canFishMove(nr, nc, sharkPos))
                {
                    //방향 저장
                    fishDirect[idx] = (fishDirect[idx] + j) % 8;
                    //물고기 교환
                    int target = mp[{nr,nc}];
                    mp[{nr, nc}] = idx;
                    mp[{fishLocate[idx].first, fishLocate[idx].second}] = target;
                    if(target>=0)
                        fishLocate[target] = { fishLocate[idx].first, fishLocate[idx].second };
                    fishLocate[idx] = { nr, nc };
                    break;
                }
            }
        }
        idx++;
        i <<= 1;
    }
}

void sharkMove(pair<int, int> sharkPos, int sharkDir, vector<pair<int, int>> fishLocate, vector<int> fishDirect, map<pair<int, int>, int> mp, short flg, int ans)
{
    if (mp[{sharkPos.first, sharkPos.second}] >= 0)
    {
        int num = mp[{sharkPos.first, sharkPos.second}];
        ans += num + 1;
        sharkDir = fishDirect[num];
        flg ^= 1 << num;
        mp[{sharkPos.first, sharkPos.second}] = -1;
    }
    else
        return;
    DFS(sharkPos, sharkDir, fishLocate, fishDirect, mp, flg, ans);
}
//먹이 먹을 때마다 해당 num + 1을 ans에 더해줌

void DFS(pair<int, int> sharkPos, int sharkDir, vector<pair<int, int>> fishLocate, vector<int> fishDirect, map<pair<int, int>, int> mp, short flg, int ans)
{
    fishMove(sharkPos, fishLocate, fishDirect, mp, flg);
    for (int i = 0; i < 3; i++)
    {
        sharkPos.first += dr[sharkDir];
        sharkPos.second += dc[sharkDir];
        if(isValidPos(sharkPos.first, sharkPos.second))
            sharkMove(sharkPos, sharkDir, fishLocate, fishDirect, mp, flg, ans);
    }
    if (answer < ans)
        answer = ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vector<pair<int, int>> fishLocate(16);
    vector<int> fishDirect(16);
    map<pair<int, int>, int> mp;
    short flg = -1;

    pair<int, int> sharkPos;
    int sharkDir;

    for (int i = 0; i < 16; i++)
    {
        int num, dir;
        cin >> num >> dir;
        fishDirect[num - 1] = dir - 1;
        fishLocate[num - 1] = { i / 4 ,i % 4 };
        mp[{i / 4, i % 4}] = num - 1;
    }

    sharkDir = fishDirect[mp[{0, 0}]];
    sharkPos = { 0 , 0 };
    flg ^= 1 << mp[{0, 0}];
    answer = mp[{0, 0}] + 1;
    mp[{0, 0}] = -1;

    DFS(sharkPos, sharkDir, fishLocate, fishDirect, mp, flg, answer);

    cout << answer;
}
