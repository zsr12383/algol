#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

//1. 회전, 2. 전체 검사해서 얼음 인접하지 않은 칸 1감소, 
//3. 얼음의 합, 4.얼음으로 연결된 덩어리 중 가장 큰 덩어리의 크기 구하기

int N, Q;
vector<vector<int>> A;
vector<vector<int>> tmp;
int L[1000];
int ans;

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

//rotate 후 A에 대입해주는 것 필요
void rotate(int r, int c, int siz)
{
    int divR = r / siz * siz;
    int divC = c / siz * siz;
    
    for(int i = r; i<r+siz;i++)
        for (int j = c; j < c + siz; j++)
        {
            int nr = i % siz;
            int nc = j % siz;
            tmp[divR + nc][divC + siz - 1 - nr] = A[i][j];
        }
}

bool isValidPos(int r, int c)
{
    return r >= 0 && r < N && c >= 0 && c < N;
}

bool decchk(int r, int c)
{
    int ret = 0;
    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (isValidPos(nr, nc) && A[nr][nc])
            ret++;
    }
    return ret <= 2;
}

void dec()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (decchk(i, j) && A[i][j] > 0)
                tmp[i][j]--;
    A = tmp;
}

int sum()
{
    int ret = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            ret += A[i][j];
    return ret;
}

void bfs(int r, int c)
{
    int cost = 1;
    tmp[r][c] = cost;
    queue<pair<int,int>> q;
    q.push({r, c});
    while (!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if (isValidPos(nr, nc) && !tmp[nr][nc] && A[nr][nc])
            {
                tmp[nr][nc] = ++cost;
                q.push({nr, nc});
            }
        }
    }
    if (ans < cost)
        ans = cost;
}

void trav() //bfs에 칸 넣을때마다 전역변수 1증가시켜서 q에 남은 거 없을 때 여태까지 값이랑 비교해서 갱신
{
    fill(tmp.begin(), tmp.end(), vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (tmp[i][j] || !A[i][j]) continue;
            bfs(i, j);
        }
}

//void print()
//{
//    cout << endl;
//    for (int i = 0; i < N; i++)
//    {
//        for (int j = 0; j < N; j++)
//            cout << A[i][j];
//        cout << endl;
//    }
//    cout << endl;
//}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> Q;
    N = 1 << N;
    A.resize(N, vector<int> (N));
    tmp.resize(N, vector<int> (N));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];
    for (int i = 0; i < Q; i++)
        cin >> L[i];

    for (int i = 0; i < Q; i++)
    {
        int siz = 1 << L[i];
        for (int j = 0; j < N; j += siz)
            for (int k = 0; k < N; k += siz)
                rotate(j, k, siz);
        A = tmp;
        dec();
    }
    trav();
    cout << sum() << "\n" << ans;
}
