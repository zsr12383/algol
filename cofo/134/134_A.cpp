#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        map<char, int> mp;
        string S1;
        string S2;
        cin >> S1 >> S2;
        mp[S1[0]]++;
        mp[S1[1]]++;
        mp[S2[0]]++;
        mp[S2[1]]++;
        cout << mp.size() - 1 << "\n";
    }
}