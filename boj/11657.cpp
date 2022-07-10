#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug
unordered_map <int, int> V[501];
ll dist[501];
int N, M;
bool isCycle;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;

    for(int i = 2; i <=N;i++)
        dist[i] = 2e18;

    for(int i = 0 ; i < M ; i++){
        int A, B, C;
        cin >> A >> B >> C;
        if(V[A].find(B) == V[A].end() || V[A][B] > C)
            V[A][B] = C;
    }

    for(int i = 1 ; i <=N; i++)
        for(int j = 1 ; j <= N ; j++) {
            if(dist[j] == 2e18) continue;
            for (auto it: V[j]) {
                int next = it.first;
                int cost = it.second;
                if (dist[next] > dist[j] + cost) dist[next] = dist[j] + cost;
            }
        }

    for(int j = 1; j<=N;j++) {
        if (dist[j] == 2e18) continue;
        for (auto it: V[j]) {
            if (dist[j] == 2e18) continue;
            int next = it.first;
            int cost = it.second;
            if (dist[next] > dist[j] + cost) {
                cout << "-1\n";
                return 0;
            }
        }
    }

    for(int i = 2; i <= N; i++){
        if(dist[i]==2e18)dist[i] = -1;
        cout << dist[i] << "\n";
    }

}
