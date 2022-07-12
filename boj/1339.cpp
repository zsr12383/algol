#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

string S[10];
set<char> MP;
vector<int> V;
int mp[26];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> S[i];
        for (int j = (int)S[i].size() - 1; j >= 0; --j)
            MP.insert(S[i][j]);
    }
    int cnt = (int)MP.size();
    for (auto it : MP)
        V.push_back(it);
    
    do {
        int sum = 0;
        for (int i = 0; i < cnt; i++)
            mp[V[i] - 'A'] = 9 - i;

        for (int i = 0; i < n; i++)
        {
            int tmp = 0;
            for (int j = 0; j < S[i].size(); j++)
            {
                tmp *= 10;
                tmp += mp[S[i][j] - 'A'];
            }
            sum += tmp;
        }
        ans = max(ans, sum);
    } while (next_permutation(V.begin(), V.end()));
    cout << ans << "\n";
}
