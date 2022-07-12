#include<bits/stdc++.h>
using namespace std;

int dr[] = { 0, 1, 0, -1 };
int dc[] = { -1, 0, 1, 0 };
int mp[503][503], ans, N;
int curC, curR, leng = 1;

void print()
{
    for (int i = 0; i < N + 4; i++)
    {
        for (int j = 0; j < N + 4; j++)
            cout << mp[i][j] << " ";
        cout << endl;
    }
	cout << endl;
}

void fill(int dir)
{
	int sand = mp[curR][curC];
	int tmp = 0;

	mp[curR][curC] = 0;
	mp[curR + 2 * dr[dir]][curC + 2 * dc[dir]] += sand / 20;
	tmp += sand / 20;

	mp[curR + dc[dir]][curC + dr[dir]] += sand * 7 / 100;
	mp[curR - dc[dir]][curC - dr[dir]] += sand * 7 / 100;
	tmp += (sand * 7 / 100) * 2;
	mp[curR + 2 * dc[dir]][curC + 2 * dr[dir]] += sand * 2 / 100;
	mp[curR - 2 * dc[dir]][curC - 2 * dr[dir]] += sand * 2 / 100;
	tmp += (sand * 2 / 100) * 2;

	if (dc[dir])
	{
		mp[curR + 1][curC + dc[dir]] += sand / 10;
		mp[curR - 1][curC + dc[dir]] += sand / 10;
		mp[curR + 1][curC - dc[dir]] += sand / 100;
		mp[curR - 1][curC - dc[dir]] += sand / 100;
	}
	else
	{
		mp[curR + dr[dir]][curC + 1] += sand / 10;
		mp[curR + dr[dir]][curC - 1] += sand / 10;
		mp[curR - dr[dir]][curC + 1] += sand / 100;
		mp[curR - dr[dir]][curC - 1] += sand / 100;
	}
	tmp += (sand * 1 / 100) * 2;
	tmp += (sand * 1 / 10) * 2;
	mp[curR + dr[dir]][curC + dc[dir]] += sand - tmp;
}

void mov()
{
	int length = 1;
	int cnt = 0;
	while (1)
	{
		for (int i = 0; i < length; i++)
		{
			int dir = cnt % 4;
			curR += dr[dir];
			curC += dc[dir];
			fill(dir);
			//print();
			if (curR == 2 && curC == 2)
				return;
		}
		cnt++;
		if ((cnt & 1) == 0)
			length++;
	}
}

void evalSand()
{
	for (int i = 0; i <= N + 3; i++)
	{
		if (i <= 1 || i >= N + 2)
			for (int j = 0; j <= N + 3; j++)
				ans += mp[i][j];
		else
			ans += mp[i][0] + mp[i][1] + mp[i][N + 2] + mp[i][N + 3];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> mp[i + 2][j + 2];
	//cout << endl;
	//print();
	curC = curR = N / 2 + 2;
	mov();
	evalSand();
	cout << ans;
}
