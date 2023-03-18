#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG

LL square_root(int x)
{
	LL low = -1, high = x;
	LL mid, square;

	while (high > low + 1)
	{
		mid = (low + high) / 2;
		square = mid * mid;

		if (square < x)
		{
			low = mid;
		}
		else
		{
			high = mid;
		}
	}

	return high;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	int x, y;
	while (T--)
	{
		cin >> x >> y;
		int dist = y - x;
		LL n = square_root(dist);

		if (n * n == dist) {
			cout << 2 * n - 1 << "\n";
			continue;
		}
		n--;
		if (n * n + n >= dist) cout << 2 * n << "\n";
		else cout << 2 * n + 1 << "\n";
	}
}
