#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    ll ans = 0;
    auto start = clock();
    for (int i = 0; i < 2000; i++)
        for (int j = 0; j < 2000; j++)
            for (int k = 0; k < 2000; k++)
                ans++;
    auto finish = clock();
    auto duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << duration << "ÃÊ" << endl;
}
