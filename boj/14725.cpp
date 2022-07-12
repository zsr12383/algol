#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define ll long long
#define debug

struct Trie {
    unordered_map<string, bool> visit;
    map<string, Trie> mp;
};

void makeTrie(Trie &T, int k)
{
    if (!k) return;
    string str;
    cin >> str;
    if (T.visit[str]) makeTrie(T.mp[str], k - 1);
    else {
        T.visit[str] = true;
        Trie child;
        T.mp[str] = child;
        makeTrie(T.mp[str], k - 1);
    }
}

void printTrie(const Trie& T,int lev)
{
    for (const auto& it : T.mp)
    {
        for (int i = 0; i < lev; i++)
            cout << "--";
        cout << it.first << "\n";
        printTrie(it.second, lev + 1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N;
    cin >> N;
    Trie T;
    for (int i = 0; i < N; i++)
    {
        int K;
        cin >> K;
        makeTrie(T, K);
    }
    printTrie(T, 0);
}
