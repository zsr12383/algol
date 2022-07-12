#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int ans;

struct Fireball
{
    int r, c, m;
    vector<int> d;
    vector<int> v;

    Fireball() {
        r = 0;
        c = 0;
        m = 0;
        d.resize(1);
        v.resize(1);
    }
    Fireball(int row, int col, int mag, int dir, int vel) {
        r = row;
        c = col;
        m = mag;
        d.push_back(dir);
        v.push_back(vel);
    }

    void operator+=(const Fireball& ref)
    {
        m += ref.m;
        d.push_back(ref.d[0]);
        v.push_back(ref.v[0]);
    }
};

vector<Fireball> fb;
vector<Fireball> mp[51][51]; //map<pair vector<fireball>> 요것도 됏겟다

int N, M, K;

//mp 클리어 해주는 함수

int trans(int num)
{
    int tmp = (num < 0 ? -num : num) % N;
    if (num <= 0)
        return N - tmp;
    else
    {
        if (tmp == 0)
            return N - tmp;
        return tmp;
    }
}

void mov()
{
    for (auto it = fb.begin(); it!=fb.end();it++)
    {
        int nr = (*it).r + dr[(*it).d[0]] * (*it).v[0];
        int nc = (*it).c + dc[(*it).d[0]] * (*it).v[0];
        nr = trans(nr);
        nc = trans(nc);
        (*it).r = nr;
        (*it).c = nc;
        if (mp[nr][nc].empty())
            mp[nr][nc].emplace_back(*it);
        else
            mp[nr][nc][0] += *it;
    }
    fb.clear();
}

bool check(vector<int> d)
{
    bool cond = true;
    bool init = (d[0] & 1);

    for (int i = 1; i < d.size(); i++)
        if(init != (d[i] & 1))
            return true;
    return false;
}



void div()
{
    for(int i =1;i<=N;i++)
        for (int j = 1; j <= N; j++)
        {
            if (mp[i][j].empty()) continue;
            if (mp[i][j][0].v.size() >= 2)
            {
                mp[i][j][0].m /= 5;
                if (!mp[i][j][0].m) continue;
                int v = 0;
                for (auto it : mp[i][j][0].v)
                    v += it;
                v /= mp[i][j][0].v.size();
                int k = check(mp[i][j][0].d);
                for (int l = 0; l <= 6; l += 2)
                    fb.emplace_back(Fireball(mp[i][j][0].r, mp[i][j][0].c, mp[i][j][0].m, l + k, v));
            }
            else
                fb.emplace_back(mp[i][j][0]);
        }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> K;

    for (int i = 0; i < M; i++)
    {
        fb.emplace_back(Fireball());
        cin >> fb[i].r >> fb[i].c >> fb[i].m >> fb[i].v[0] >> fb[i].d[0];
    }

    while (K--)
    {
        mov();
        div();
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                mp[i][j].clear();
    }

    for (auto it : fb)
        ans += it.m;
    cout << ans;
}
