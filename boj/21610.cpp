#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

/*
* 맵인덱스 1~N
* 왼쪽아래 구석에 비바라기 생김(4칸)
* 왼쪽부터 반시계반향으로 8방향 있음
* 맵 연결돼있음
* 
* 구름 첫 이동
* 구름 있는 칸에 물 1증가
* 구름 사라짐, 사라진칸에 물복사 시작
* -> 물복사를 위한 벡터 필요, x자 방향 거리 1만큼 물이있는 수만큼 현재 바구니 물증가(이때는 연결 x)
* 
* 물양 2 이상인 곳에서 구름 생성, 물의 양 2 줄음
*/

int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
// x자 2, 4, 6, 8

int N, M;
int A[51][51];
//  방향, 속도
pair<int, int> Move[100];
vector<pair<int, int>> cloud = { {N, 1}, {N, 2}, {N - 1, 1}, {N - 1, 2} };
map<pair<int, int>, bool> mp;


int trans(int num)
{
    int tmp = num;
    tmp = tmp <= 0 ? -tmp : tmp;
    tmp %= N;
    if (num <= 0 || tmp == 0)
        return N - tmp;
    return tmp;
}

void mov(pair<int, int> info)
{
    for (auto &it : cloud)
    {
        int nr = it.first + dr[info.first] * info.second;
        int nc = it.second + dc[info.first] * info.second;
        nr = trans(nr);
        nc = trans(nc);
        it.first = nr;
        it.second = nc;
        A[nr][nc]++;
    }
}

bool isValidPos(int r, int c)
{
    return r >= 1 && r <= N && c >= 1 && c <= N;
}

void bug()
{
    for (auto& it : cloud)
    {
        int cnt = 0;
        for (int i = 2; i <= 8; i += 2)
        {
            int nr = it.first + dr[i];
            int nc = it.second + dc[i];
            if (isValidPos(nr, nc)&& A[nr][nc])
                cnt++;
        }
        A[it.first][it.second] += cnt;
        mp[{it.first, it.second}] = true;
    }
    cloud.clear();
}

void create()
{
    for(int i = 1; i<=N;i++)
        for(int j = 1; j<=N;j++)
            if (A[i][j] >= 2 && !mp[{i, j}])
            {
                A[i][j] -= 2;
                cloud.push_back({i, j});
            }
    mp.clear();
}

int eval()
{
    int ret = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            ret += A[i][j];
    return ret;
}

void print()
{
    cout << endl;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> A[i][j];
    for (int i = 0; i < M; i++)
        cin >> Move[i].first >> Move[i].second;

    for (int i = 0; i < M; i++)
    {
        mov(Move[i]);
        bug();
        create();
    }
    cout << eval();
}
