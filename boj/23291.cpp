#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

/*
* 물고기 최소인 어항들에 한마리 추가
* 공중부양
* 인접한 어항 사이에서 물고기 많은 곳에서 적은 곳으로 diff / 5마리 보냄( 모든 칸에서 동시에 이뤄져야함 <- 임시배열 필요)
* 다시 일렬로 만들기
* 반접어 180도회전 두번하고 다시 정리
* 일렬에 놓기
* 이것이 한번의 사이클일 때 가장 큰 물고기와 가장 적은 물고기의 차이가 K이하가 되려면 몇번 반복해야하는지
*/

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int ans;
int N, K, mx, mn;
vector<vector<int>> squ;
deque<int> line;

bool isValidPos(int r, int c, int h, int w)
{
	return r >= 0 && c >= 0 && r < h && c < w;
}

int eval()
{
	mx = -1, mn = INT_MAX;
	for (auto it : line)
	{
		if (it > mx)
			mx = it;
		if (it < mn)
			mn = it;
	}
	return mx - mn;
}

void mininc()
{
	for (auto& it : line)
		if (it == mn)
			it++;
}

void rotate()
{
	vector<vector<int>> tmp(squ[0].size(), vector<int>(squ.size()));
	for (int i = 0; i < squ.size(); i++)
		for (int j = 0; j < squ[0].size(); j++)
			tmp[j][squ.size() - 1 - i] = squ[i][j];
	squ = tmp;
}

void levitation()
{
	squ.clear();
	squ.push_back(vector<int>());
	squ[0].push_back(line[0]);
	line.pop_front();
	int i = 2;
	while (squ.size() <= line.size())
	{
		//회전하고
		rotate();
		//아래에 추가하고
		squ.push_back(vector<int>(squ[0].size()));
		for (int j = 0; j < squ[0].size(); j++)
		{
			squ[i / 2][j] = line[0];
			line.pop_front();
		}
		i++;
	}
	for (int i = 0; i < squ.size() - 1; i++)
		squ[i].resize(squ[i].size() + line.size());
	for (int i = 0; i < line.size();)
	{
		squ.back().push_back(line[0]);
		line.pop_front();
	}
}

void adjust()
{
	auto tmp = squ;
	for(int i = 0 ; i<squ.size();i++)
		for (int j = 0; j < squ[0].size(); j++)
			for (int d = 0; d < 4; d++)
			{
				int nr = i + dr[d];
				int nc = j + dc[d];
				if (isValidPos(nr, nc, squ.size(), squ[0].size()) && squ[i][j] && squ[nr][nc] && squ[i][j] > squ[nr][nc])
				{
					int change = (squ[i][j] - squ[nr][nc]) / 5;
					tmp[nr][nc] += change;
					tmp[i][j] -= change;
				}
			}
	squ = tmp;
}

void spread()
{
	line.clear();
	for (int i = 0; i < squ[0].size(); i++)
		for (int j = squ.size() - 1; j >= 0; j--)
			if(squ[j][i])
				line.push_back(squ[j][i]);
}

void levitation2()
{
	int siz = line.size() / 4;
	squ.resize(4);
	for (auto& it : squ)
		it.resize(siz);
	for (int j = 0; j < siz; j++)
	{
		squ[0][j] = line[3 * siz - 1- j];
		squ[1][j] = line[siz + j];
		squ[2][j] = line[siz - 1 - j];
		squ[3][j] = line[3 * siz + j];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;
	line.resize(N);
	for (int i = 0; i < N; i++)
	{
		int tmp;
		cin >> tmp;
		line[i] = tmp;
	}

	while (eval() > K)
	{
		ans++;
		mininc();
		levitation();
		adjust();
		spread();
		levitation2();
		adjust();
		spread();
	}
	cout << ans;
}
