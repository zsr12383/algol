#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int W, H;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

char mp[100][100];
int vst[100][100][4];
pair<int, int> cur;

bool isValidPos(int r, int c)
{
	return r >= 0 && r < H && c >= 0 && c < W;
}

struct MoveInfo
{
	int r, c, dist, cost, prevDir;
};

int bfs()
{
	queue<MoveInfo> q;
	q.push({cur.first, cur.second, 0, -1, -1});
	mp[cur.first][cur.second] = '*';
	int ans = INT_MAX;
	while (!q.empty())
	{
		auto tmp = q.front();
		auto [r, c, dist, cost, prevDir] = tmp;
		q.pop();
		if (mp[r][c] == 'C')
		{
			ans = min(ans, vst[r][c][prevDir]);
			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (!isValidPos(nr, nc) || mp[nr][nc] == '*')
			{
				continue;
			}
			if (prevDir != i && vst[nr][nc][i] > cost + 1)
			{
				q.push({nr, nc, dist + 1, cost + 1, i});
				vst[nr][nc][i] = cost + 1;
			}
			else if (prevDir == i && vst[nr][nc][i] > cost)
			{
				vst[nr][nc][i] = cost;
				q.push({nr, nc, dist + 1, cost, i});
			}
		}
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> W >> H;

	for (int i = 0; i < H; i++)
	{
		string tmp;
		cin >> tmp;
		for (int j = 0; j < W; j++)
		{
			mp[i][j] = tmp[j];
			for (int k = 0; k < 4; k++)
				vst[i][j][k] = INT_MAX;
			if (tmp[j] == 'C')
			{
				cur.first = i;
				cur.second = j;
			}
		}
	}
	cout << bfs();
}
