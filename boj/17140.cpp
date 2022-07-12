#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

vector<vector<int>> V(3, vector<int>(3));
int R, C, K;
int ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> R >> C >> K;
    for (int i = 0; i <3; i++)
        for (int j = 0; j < 3; j++)
            cin >> V[i][j];
    while (R > V.size() || C > V[0].size() || V[R - 1][C - 1] != K)
    {
        if (ans == 100) {
            ans = -1;
            break;
        }
        ans++;

        if (V.size() >= V[0].size())
        {
            int mx = 0;
            for (int i = 0; i < V.size(); i++)
            {
                map<int, int> mp;
                vector<pair<int, int>> tmp;
                vector<int> tmp2;
                for (int j = 0; j < V[i].size(); j++)
                {
                    if(V[i][j])
                        mp[V[i][j]]++;
                }
                for (auto it : mp)
                    tmp.push_back({it.second, it.first});
                sort(tmp.begin(), tmp.end());
                for (auto it : tmp)
                {
                    tmp2.push_back(it.second);
                    tmp2.push_back(it.first);
                }
                V[i] = tmp2;
                if (mx < V[i].size())
                    mx = V[i].size();
            }
            for (int i = 0; i < V.size(); i++)
                V[i].resize(mx, 0);
        }

        else
        {
            int mx = 0;
            vector<vector<int>> tmp2;
            for (int i = 0; i < V[0].size(); i++)
            {
                map<int, int> mp;
                vector<pair<int, int>> tmp;
                
                for (int j = 0; j < V.size(); j++)
                    if(V[j][i])
                        mp[V[j][i]]++;
                for (auto it : mp)
                    tmp.push_back({ it.second, it.first });
                sort(tmp.begin(), tmp.end());
                if (tmp2.size() < tmp.size() * 2)
                    tmp2.resize(tmp.size() * 2, vector<int>(V[0].size(), 0));
                for (int j = 0; j < tmp.size(); j++)
                {
                    tmp2[j * 2][i] = tmp[j].second;
                    tmp2[j * 2 + 1][i] = tmp[j].first;
                }
            }
            V = tmp2;
        }
    }
    cout << ans;
}
