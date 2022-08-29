#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int n;
int a[200000];
int b[200000];
int c[200000];
int d[200000];
map<int, int> mp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            mp[b[i]]++;
        }
        for (int i = n - 1; i >= 0; i--) {
            int idx = lower_bound(b, b + i + 1, a[i]) - b;
            c[i] = b[idx] - a[i];
        }
        for (int i = n - 1; i >= 0; i--) {
            auto it = mp.lower_bound(a[i]);
            d[i] = (*(mp.rbegin())).first - a[i];
            (*(it)).second--;
            if ((*(it)).second == 0)
                mp.erase((*(it)).first);
        }
        for (int i = 0; i < n; i++) {
            cout << c[i] << " ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++) {
            cout << d[i] << " ";
        }
        cout << "\n";
    }
}