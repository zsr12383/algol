#include <bits/stdc++.h>

#define all(v) v.begin(), v.end()
#define var(x, y, z) cout << x << " " << y << " " << z << endl;
#define ll long long int
#define pii pair<ll, ll>
#define pb push_back
#define ff first
#define ss second
#define FASTIO                \
    ios ::sync_with_stdio(0); \
    cin.tie(0);               \
    cout.tie(0);

using namespace std;

const ll inf = 1e17;
const ll MAXM = 1e5;
vector<ll> factors[MAXM + 5];

void init() {
    for (ll i = 1; i <= MAXM; i++) {
        for (ll j = i; j <= MAXM; j += i) {
            factors[j].pb(i);
        }
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector <pii> vec;
    for (ll i = 0; i < n; i++) {
        ll value;
        cin >> value;
        vec.pb({value, i});
    }
    sort(all(vec));
    vector<ll> frequency(m + 5, 0);
    ll curr_count = 0;
    ll j = 0;
    ll global_ans = inf;
    for (ll i = 0; i < n; i++) {
        for (auto x: factors[vec[i].ff]) {
            if (x > m)
                break;
            if (!frequency[x]++) {
                curr_count++;
            }
        }
        while (curr_count == m) {
            ll curr_ans = vec[i].ff - vec[j].ff;
            if (curr_ans < global_ans) {
                global_ans = curr_ans;
            }
            for (auto x: factors[vec[j].ff]) {
                if (x > m)
                    break;
                if (--frequency[x] == 0) {
                    curr_count--;
                }
            }
            j++;
        }
    }
    cout << (global_ans >= inf ? -1 : global_ans) << "\n";
}

int main() {
    FASTIO
    init();
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}