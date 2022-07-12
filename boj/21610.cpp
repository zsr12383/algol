#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

/*
* ���ε��� 1~N
* ���ʾƷ� ������ ��ٶ�� ����(4ĭ)
* ���ʺ��� �ݽð�������� 8���� ����
* �� ���������
* 
* ���� ù �̵�
* ���� �ִ� ĭ�� �� 1����
* ���� �����, �����ĭ�� ������ ����
* -> �����縦 ���� ���� �ʿ�, x�� ���� �Ÿ� 1��ŭ �����ִ� ����ŭ ���� �ٱ��� ������(�̶��� ���� x)
* 
* ���� 2 �̻��� ������ ���� ����, ���� �� 2 ����
*/

int dr[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
// x�� 2, 4, 6, 8

int N, M;
int A[51][51];
//  ����, �ӵ�
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
