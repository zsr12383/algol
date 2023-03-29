#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG
int N, E;
LL dist[801][801];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> N >> E;
	int a, b, c, v1, v2;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			if(i != j)dist[i][j] = (LL)1E17;
		}
	for (int i = 0; i < E; i++)
	{
		cin >> a >> b >> c;
		dist[a][b] = c;
		dist[b][a] = c;
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			for (int k = 1; k <= N; k++)
			{
				dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
			}
		}
	}
	cin >> v1 >> v2;
	LL ans = min(dist[1][v1] + dist[v1][v2] + dist[v2][N], dist[1][v2] + dist[v2][v1] + dist[v1][N]);
	ans = ans >= (LL)1E17 ? -1 : ans;
	cout << ans << "\n";
}
