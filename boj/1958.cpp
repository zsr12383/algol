#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug
int D[1001];
int t[1001];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<unordered_map<int, bool>> inn(N + 1);
        vector<unordered_map<int, bool>> ou(N + 1);
        memset(t, 0, sizeof(t));
        for (int i = 0; i < N; i++)
            cin >> D[i + 1];
        for (int i = 0; i < K; i++) {
            int A, B;
            cin >> A >> B;
            inn[B][A] = true;
            ou[A][B] = true;
        }
        queue<pair<int, int>> q;
        for (int i = 1; i <= N; i++) {
            if (inn[i].empty())
                q.push({ i, D[i]});
        }
        int dest;
        cin >> dest;
        int now = 0, cost = 0;

        while (!q.empty()) {
            now = q.front().first;
            cost = q.front().second;
            q.pop();
            if (now == dest) break;
            for (auto it : ou[now]) {
                t[it.first] = max(t[it.first], cost);
                inn[it.first].erase(now);
                if (inn[it.first].empty())
                    q.push({it.first, t[it.first] + D[it.first]});
            }
            ou[now].clear();
        }
        cout << cost << "\n";
    }
}
