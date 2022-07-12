#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug
int l[100000];
int r[100000];
int h[100000];
stack<pair<int, int>> S; // idx, h

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int N;
    ll ans = 0 ;
    cin >> N;

    memset(l, -1, sizeof(l));
    for (int i = 0; i < N; i++)
        r[i] = N;

    for (int i = 0; i < N; i++) {
        cin >> h[i];
        while (S.size() && S.top().second >= h[i]) {
            r[S.top().first] = i;
            S.pop();
        }
        int lidx = S.size() ? S.top().first : -1;
        l[i] = lidx;
        S.push({i, h[i]});
    }
    for (int i = 0; i < N; i++)
        ans = max(ans, (ll)(r[i] - l[i] - 1)*h[i]);
    cout << ans << "\n";
}
