#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
int n, m, sr, sc, d;
int mp[1001][1001];

int evalDistance(int r1, int c1, int r2, int c2) {
	return abs(r1 - r2) + abs(c1 - c2);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;

	while (t--)
	{
		cin >> n >> m >> sr >> sc >> d;
		if (evalDistance(n, m, sr, sc) <= d) {
			cout << "-1\n";
			continue;
		}

		int u = sr - d;
		int down = sr + d;
		int l = sc - d;
		int r = sc + d;
		if (l <= 1 && r >= m) {
			cout << "-1\n";
			continue;
		}
		if (u <= 1 && down >= n) {
			cout << "-1\n";
			continue;
		}
		if (l <= 1 && u <= 1) {
			cout << "-1\n";
			continue;
		}
		if (r >= m && down >= n) {
			cout << "-1\n";
			continue;
		}
		cout << (n - 1) + (m - 1) << "\n";
	}
}