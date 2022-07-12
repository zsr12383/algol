#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

bool isPrime(int n) {
    if (n == 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;
    vector<int> V;
    V.push_back(0);
    for (int i = 0; i < N; i++) {
        vector<int> V2;
        for (auto it : V) {
            int num = it;
            num *= 10;
            for (int i = 1; i < 10; i++) {
                int tmp = num + i;
                if (isPrime(tmp))
                    V2.push_back(tmp);
            }
        }
        V = V2;
    }
    sort(V.begin(), V.end());
    for (auto it : V)
        cout << it << "\n";
}
