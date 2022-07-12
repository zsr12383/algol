#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

/*
* 한칸에는 한명만 가능
* 학생이 좋아하는 사람 4명
* 번호는 1~N, 학생수 N^2
* 상하좌우 인접
* 
* 1) 좋아하는 학생이 가장 많이 인접한 칸
* 2) 그중 인접한 칸중 비어있는 칸이 많은 칸으로 감
* 3) 그것도 안되면 행작고 열작은 순서로
* 1,2,3 다하고 소트 돌려보기(안되면 진짜 정보 담아서 해야할듯)
* 자리 배치가 끝난 후 만족도 구함 0 -> 0, 1-> 1, 2-> 10, 3-> 100, 4-> 1000
*/

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

struct Student {
    unordered_map<int, bool> Pre;
};

int N, M;
Student S[401];
queue<int> q;
int mp[21][21];

bool isValidPos(int r, int c)
{
    return r >= 0 && r < N&& c >= 0 && c < N;
}

void pick(int n)
{
    vector < pair<int, pair<int, pair<int, int>>>> V;

    for(int i = 0 ; i<N;i++)
        for (int j = 0; j < N; j++)
        {
            if (mp[i][j]) continue;
            int frd = 0, emp = 0;
            for (int k = 0; k < 4; k++)
            {
                int nr = i + dr[k];
                int nc = j + dc[k];
                if (isValidPos(nr, nc))
                {
                    if (!mp[nr][nc]) emp++;
                    else if (S[n].Pre[mp[nr][nc]]) frd++;
                }
            }
            V.push_back({ -frd, {-emp, {i, j} } });
        }
    sort(V.begin(), V.end());
    mp[V[0].second.second.first][V[0].second.second.second] = n;
}

int eval()
{
    int ans = 0;
    for(int i = 0 ; i < N;i++)
        for (int j = 0; j < N; j++)
        {
            int howmany = 0;
            for (int k = 0; k < 4; k++)
            {
                int nr = i + dr[k];
                int nc = j + dc[k];
                if (isValidPos(nr, nc) && S[mp[i][j]].Pre[mp[nr][nc]])
                    howmany++;
            }
            if (howmany)
                ans += pow(10, howmany - 1);
        }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    M = N * N;
    for (int i = 0; i < M; i++)
    {
        int idx, a, b, c, d;
        cin >> idx >> a >> b >> c >> d;
        q.push(idx);
        S[idx].Pre[a] = true; 
        S[idx].Pre[b] = true; 
        S[idx].Pre[c] = true; 
        S[idx].Pre[d] = true;
    }

    while (!q.empty())
    {
        int num = q.front();
        q.pop();
        pick(num);
    }
    cout << eval();
}
