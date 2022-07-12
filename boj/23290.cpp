#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

/*
* 4*4 ��
* 
* ����� M����, ��� 1, ������1
* ������� ������ ���� ĭ ����
* 1. ����� ������ ���常 �صΰ� ���� ������ x
* 2. ����Ⱑ ��ĭ�� �̵�(���, ���� �ִ� �� x, ����� ��x �̵� ������ ������ 45�� ȸ��, �̵� �Ұ��� �̵� x)
* 3. ��� ���� 3ĭ �̵�(3, 5, 7, 1 vst + dfs�� ����?, �Ϲ� �����̸� ��¦ ��ȿ���� �ֱ��ҵ�), �����¿��, ���� ����� �׸��δ� �̵� �Ұ�, ����� �ִ� ĭ���� �� �� ����� ����, ���ܵǴ� ������ ������ ����
* �� �� �̵� ������ ���� ���� ����Ⱑ ���ܵǴ� ��������, �������� �� ��� ���� ������ �ռ��� ���
* 4. �δܰ��� �������� ���� ������ �������.(life�� ���� �ΰ� �ʱⰪ 2�� �θ� �ɵ�)
* 5. �����Ϸ� 1������ ��ġ�� ����
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
    //��ü ��ȸ�ϸ鼭 �� ĭ�� �� ��ȸ�ϸ鼭 �̵� �������� ���� �˻� �� �ݴ�� �̽� ���ְ� ���� �ε����� �迭�� �����س��ٰ� ������;
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
        if (!isValidPos(nr, nc)) continue; //�Դ� ���� ���� �ǳ�? ��, ��� ���� �ƴ϶� �Ǿ�߸� ����
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
    // rout ��� ���ΰ��鼭 ���� ������ ���̱�, ��� 3 �����
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
