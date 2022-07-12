#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

string stk;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string tmp;
    cin >> tmp;
    for (auto c : tmp)
    {
        stk.push_back(c);
        if (c == 'A')
            continue;
        while (stk.size() >= 4 && stk.substr(stk.size() - 4) == "PPAP")
            for (int i = 0; i < 3; i++)
                stk.pop_back();
    }
    if (stk == "P")
        cout << "PPAP";
    else
        cout << "NP";
}
