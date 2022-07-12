#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

/*
* N * N ����, �� ĭ���� ����� �ϳ��� ����
* ����� ����(-1), ������(0), �Ϲ�(M���� ����)
* �����¿찡 ������ ĭ
* ����� ���� ��ϱ׷�, �׷쿡�� �Ϲ� ��� �ϳ� �־���ϰ� �Ϲ� ��ϳ��� ���� ��, ���� ����� �������
* �׷��� ����� ������ 2�̻�, ���� ����� �Ϲ� ��� �� ��, ���� ��ȣ�� ���� ���� ��
* 
* ũ�� ū ��� -> ������ ��� ���� ��� -> ���� ����� �� ū �� -> �� ū�� ã�� ��� ����, ������ ������ŭ ���� ȹ��
* �߷� �ۿ�(-1 ���� �ٶ�����, -1�� ������)
* �ݽð� 90�� ȸ��
* �߷� �ۿ�
*/

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int N, M, ans;
vector<vector<int>> mp(20, vector<int>(20));
int vst[20][20];

struct Block {
    int siz;
    int rainbow;
    pair<int, int> pos;
    vector<pair<int, int>> tar;
};

vector<Block>V;

bool isValisPos(int r, int c)
{
    return r >= 0 && r < N&& c >= 0 && c < N;
}

pair<int, int> findMin(pair<int, int> A, pair<int, int> B)
{
    if (A.first == B.first)
        if (A.second < B.second)
            return A;
        else
            return B;
    if (A.first > B.first)
        return B;
    return A;
}



void bfs(int r, int c, int color)
{
    Block tmp;
    tmp.siz = 1;
    tmp.rainbow = 0;
    tmp.pos = { r, c };
    tmp.tar.push_back({ r, c });
    vst[r][c] = 1;
    
    for(int i = 0 ; i<N;i++)
        for (int j = 0; j < N; j++)
        {
            if (mp[i][j] == 0)
                vst[i][j] = 0;
        }

    queue<pair<int, int>> q;
    q.push({r,c});
    while (!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if (isValisPos(nr, nc) && !vst[nr][nc] && (mp[nr][nc] == color || !mp[nr][nc]))
            {
                tmp.siz++;
                tmp.tar.push_back({nr, nc});
                if (mp[nr][nc])
                    tmp.pos = findMin(tmp.pos, { nr, nc });
                else
                    tmp.rainbow++;
                vst[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    if(tmp.siz >1)
        V.push_back(tmp);
}

int srch()
{
    V.clear();
    memset(vst, 0, sizeof(vst));
    for(int i = 0 ;i<N;i++)
        for (int j = 0; j < N; j++)
        {
            if (mp[i][j] <= 0) continue;
            if (vst[i][j]) continue;
            bfs(i, j, mp[i][j]);
        }
    return V.size();
}

bool comp(Block &A, Block &B)
{
    if (A.siz > B.siz) return true;
    else if (A.siz < B.siz) return false;
    else
    {
        if (A.rainbow > B.rainbow) return true;
        else if (A.rainbow < B.rainbow) return false;
        else
        {
            if (A.pos.first > B.pos.first) return true;
            else if (A.pos.first < B.pos.first) return false;
            else
                return A.pos.second > B.pos.second;
        }
    }
}

void del()
{
    sort(V.begin(), V.end(), comp);
    ans += V[0].siz * V[0].siz;
    for (auto it : V[0].tar)
    {
        mp[it.first][it.second] = -2;
    }
}

void grav()
{
    for (int c = 0; c < N; c++)
    {
        int r = N - 1;
        while (r >=0)
        {
            int pos = r;
            queue<int> q;
            while (r >=0 && mp[r][c] != -1)
            {
                if(mp[r][c] != -2)
                    q.push(mp[r][c]);
                r--;
            }
            while (!q.empty())
            {
                int num = q.front();
                q.pop();
                mp[pos--][c] = num;
            }
            while (pos > r)
                mp[pos--][c] = -2;
            r--;
        }
    }
}

void rotate()
{
    auto tmp = mp;
    for(int i = 0 ; i< N;i++)
        for (int j = 0; j < N; j++)
        {
            tmp[N - 1 -j][i] = mp[i][j];
        }
    mp = tmp;
}

void print()
{
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mp[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> mp[i][j];

    while (srch())
    {
        //print();
        del();
        //print();
        grav();
        //print();
        rotate();
        //print();
        grav();
        //print();
    }
    cout << ans;
}
