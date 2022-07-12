#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int n, m, x, y, k;
int mp[20][20];

int dr[] = {0, 0, 0, -1, 1 };
int dc[] = {0, 1, -1, 0, 0 };

deque<int> ud = {0, 0, 0, 0};
deque<int> lr = {0, 0, 0, 0};

bool isValidPos(int r, int c)
{
    return r >= 0 && r < n&& c >= 0 && c < m;
}

void rotate(int dir)
{
    switch (dir)
    {
    case 1:
        lr.push_back(lr.front());
        lr.pop_front();
        ud[0] = lr[0];
        ud[2] = lr[2];
        break;
    case 2:
        lr.push_front(lr.back());
        lr.pop_back();
        ud[0] = lr[0];
        ud[2] = lr[2];
        break;
    case 3:
        ud.push_front(ud.back());
        ud.pop_back();
        lr[0] = ud[0];
        lr[2] = ud[2];
        break;
    case 4:
        ud.push_back(ud.front());
        ud.pop_front();
        lr[0] = ud[0];
        lr[2] = ud[2];
        break;
    default:
        break;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> x >> y >> k;

    for(int i = 0 ; i < n ; i++)
        for (int j = 0; j < m; j++)
            cin >> mp[i][j];

    ud[0] = mp[x][y];
    lr[0] = mp[x][y];
    mp[x][y] = 0;
    
    for (int i = 0; i < k; i++)
    {
        int dir;
        cin >> dir;
        int dx = x + dr[dir];
        int dy = y + dc[dir];
        if (isValidPos(dx, dy))
        {
            x = dx;
            y = dy;
            rotate(dir);
            if (mp[x][y])
            {
                ud[0] = mp[x][y];
                lr[0] = mp[x][y];
                mp[x][y] = 0;
            }
            else
            {
                mp[x][y] = ud[0];
            }
            cout << ud[2] << "\n";
        }
    }
}
