#include<bits/stdc++.h>
using namespace std;
int N, M, K, R, C;
string answer;
bool vst[50][50][2500];
int dr[] = {1, 0, 0, -1};
int dc[] = {0, -1, 1, 0};
string dSTR = "dlru";
bool btn = false;

int getDistance(int x, int y, int r, int c)
{
	return abs(x - r) + abs(y - c);
}


bool isValidPos(int r, int c)
{
	return r >= 0 && r < N && c >= 0 && c < M;
}

void dfs(int currentR, int currentC, int step)
{
	if (currentR == R && currentC == C && step == K)
	{
        btn = true;
		return;
	}
	step++;
	for (int i = 0; i < 4; i++)
	{
		int nr = currentR + dr[i];
		int nc = currentC + dc[i];
		if (!isValidPos(nr, nc)) continue;
		if (getDistance(currentR, currentC, R, C) > K + 1 - step) continue;
		if (vst[nr][nc][step]) continue;
		vst[nr][nc][step] = true;
        answer.push_back(dSTR[i]);
		dfs(nr, nc, step);
        if (btn) return;
        answer.pop_back();		
	}
}

string solution(int n, int m, int x, int y, int r, int c, int k)
{
	N = n, M = m, K = k, R = r - 1, C = c - 1;
	x--, y--;
	dfs(x, y, 0);
	if (!btn) answer = "impossible";
	return answer;
}