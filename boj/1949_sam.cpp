#include<bits/stdc++.h>
using namespace std;

int arr[9][9];
bool vst[9][9];
int T, N, K, mx = -1;
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };
int ans = 0;

bool isvalidpos(int x, int y)
{
	return x >= 0 && x < N&& y >= 0 && y < N && !vst[x][y];
}

void dfs(int x, int y, bool cancut, int depth)
{
	if (ans < depth)
		ans = depth;
	vst[x][y] = true;
	for (int i = 0; i < 4; i++)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (isvalidpos(nx, ny))
		{
			if (arr[x][y] > arr[nx][ny])
				dfs(nx, ny, cancut, depth + 1);
			else
			{
				if (cancut && arr[x][y] > arr[nx][ny] - K)
				{
					int tmp = arr[nx][ny];
					arr[nx][ny] = arr[x][y] - 1;
					dfs(nx, ny, false, depth + 1);
					arr[nx][ny] = tmp;
				}
			}
		}
	}
	vst[x][y] = false;
}

int main(int argc, char** argv)
{
	cin >> T;
	int i = 1;
	while (T--)
	{
		cin >> N >> K;
		memset(arr, 0, sizeof(arr));
		mx = -1;
		ans = 0;
		map<pair<int, int>, bool> mp;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				cin >> arr[i][j];
				if (mx < arr[i][j])
					mx = arr[i][j];
			}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				if (arr[i][j] == mx)
					mp[{i, j}] = true;
			}

		map<pair<int, int>, bool>::iterator iter = mp.begin();
		for (iter; iter != mp.end(); iter++)
		{
			dfs((*iter).first.first, (*iter).first.second, true, 1);
		}
		cout << "#" << i << " " << ans << "\n";
		i++;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
