#include<iostream>
#include<vector>

#define endl "\n"
#define MAX 101
using namespace std;

int N, x, y, d, g, Sx, Sy;
int MAP[MAX][MAX];

int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0 ,-1 ,0 };

vector<int> Dir_Info;

void Input()
{
    cin >> N;
}

void Make_Dragon_Curve()
{
    int S = Dir_Info.size();
    for (int i = S - 1; i >= 0; i--)
    {
        int nD = (Dir_Info[i] + 1) % 4;
        x = x + dx[nD];
        y = y + dy[nD];
        MAP[x][y] = 1;

        Dir_Info.push_back(nD);
    }
}

void Count_Square()
{
    int Cnt = 0;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (MAP[i][j] == 1 && MAP[i + 1][j] == 1 &&
                MAP[i][j + 1] == 1 && MAP[i + 1][j + 1] == true)
            {
                Cnt++;
            }
        }
    }
    cout << Cnt << endl;
}

void Solution()
{
    for (int i = 0; i < N; i++)
    {
        cin >> y >> x >> d >> g;

        Dir_Info.clear();

        MAP[x][y] = 1;
        x = x + dx[d];
        y = y + dy[d];
        MAP[x][y] = 1;

        Dir_Info.push_back(d);
        for (int j = 0; j < g; j++)
        {
            Make_Dragon_Curve();
        }
    }

    Count_Square();
}

void Solve()
{
    Input();
    Solution();
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //freopen("Input.txt", "r", stdin);
    Solve();

    return 0;
}
