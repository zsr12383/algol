#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	priority_queue<LL> pq;
	int N, tmp;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		pq.push(-tmp);
	}
	LL ans = 0;
	while(pq.size()>=2)
	{
		LL v1 = pq.top();
		pq.pop();
		LL v2 = pq.top();
		pq.pop();
		LL adder = v1 + v2;
		pq.push(adder);
		ans += adder;
	}
	cout << -ans << "\n";
}
