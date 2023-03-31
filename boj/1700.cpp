#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG

set<int> currentList;
queue<int> V[101];
queue<int> order;
int N, K, tmp, ans;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> N >> K;
	for(int i = 0 ; i < K ; i++)
	{
		cin >> tmp;
		V[tmp].push(i);
		order.push(tmp);
	}
	while(!order.empty())
	{
		int item = order.front();
		order.pop();
		if(currentList.find(item) != currentList.end())
		{
			V[item].pop();
			continue;
		}
		if((int)currentList.size() < N)
		{
			currentList.insert(item);
			V[item].pop();
			continue;
		}
		int candidate, distance = 0;
		for(auto num : currentList)
		{
			if(V[num].empty())
			{
				candidate = num;
				break;
			}
			if(distance < V[num].front())
			{
				candidate = num;
				distance = V[num].front();
			}
		}
		currentList.erase(candidate);
		currentList.insert(item);
		ans++;
		if(V[item].empty()) continue;
		V[item].pop();
	}
	cout << ans << "\n";
}
