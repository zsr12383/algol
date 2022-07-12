#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

/*
* N * M맵, 지도에는 정수 하나씩 있음
* 위1 우3인 채로 (1, 1) 놓여짐
* 주사위는 굴러서 이동, 이동 방향이 없다면 반대로
* 해당 칸의 점수 획득, 주사위 밑면과 해당 칸의 수 비교해서 이동방향 결정(같으면 그대로 주사위 밑면이 칸보다 크면 시계 작으면 반시계 회전)
* 점수 구하는 계산은 해당 칸이 포함된 같은 숫자 넓이 구하는 것 <- 점수용 배열을 만들자
*/

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

deque<int> lr = { 4, 1, 3, 6 };
deque<int> ud = { 2, 1, 5, 6 };


int N, M, K;
int mp[20][20];
int* ptr[20][20];
int di[400];
int cnt;
int dir;
pair<int, int> cur;
int ans;

bool isValidPos(int r, int c)
{
    return r >= 0 && r < N&& c >= 0 && c < M;
}

//벡터에 넣고 후에 다시 다 최신화 하는거보다 포인터로 가리키게 한 것 굿 아이디어인듯
void bfs(int r, int c, int num)
{
    ptr[r][c] = &di[cnt];
    di[cnt] += num;
    queue<pair<int, int>> q;
    q.push({ r, c });
    while (!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if (isValidPos(nr, nc) && !ptr[nr][nc] && mp[nr][nc] == num)
            {
                ptr[nr][nc] = &di[cnt];
                di[cnt] += num;
                q.push({ nr, nc });
            }
        }
    }
    cnt++;
}

void getptr()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            if (ptr[i][j]) continue;
            bfs(i, j, mp[i][j]);
        }
}

void mov(int d)
{
    cur.first += dr[d];
    cur.second += dc[d];
    if (!isValidPos(cur.first, cur.second))
    {
        d += 2;
        d %= 4;
        cur.first += 2 * dr[d];
        cur.second += 2 * dc[d];
    }

    if (d == 0)
    {
        ud.push_back(ud[0]);
        ud.pop_front();
        lr[1] = ud[1];
        lr[3] = ud[3];
    }
    else if (d == 1)
    {
        lr.push_front(lr.back());
        lr.pop_back();
        ud[1] = lr[1];
        ud[3] = lr[3];
    }
    else if (d == 2)
    {
        ud.push_front(ud.back());
        ud.pop_back();
        lr[1] = ud[1];
        lr[3] = ud[3];
    }
    else if (d == 3)
    {
        lr.push_back(lr[0]);
        lr.pop_front();
        ud[1] = lr[1];
        ud[3] = lr[3];
    }
    
    ans += *ptr[cur.first][cur.second];

    if (mp[cur.first][cur.second] > lr[3])
        dir = d - 1;
    else if (mp[cur.first][cur.second] < lr[3])
        dir = d + 1;
    else
        dir = d;

    if (dir >= 4)
        dir %= 4;
    else if (dir < 0)
        dir = 4 + dir;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> K;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> mp[i][j];

    getptr();

    mov(1);

    for (int i = 0; i < K - 1; i++)
    {
        mov(dir);
    }
    cout << ans;
}
