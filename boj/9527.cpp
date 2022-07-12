#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

ll dq(ll A, ll B)
{
    ll k = 1;
    ll i = 0, j = 0;
    while (k < B)
        k <<= 1;
    i = k;
    while (k < A)
        k <<= 1;
    k /= 2;
    return k - i + dq(A, K) + dq(K, B);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int A, B;
    cin >> A >> B;
    cout << dq(B, A) << endl;
}
