#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

vector<pair<int, int>> linkList[100001];
bool vst[100001];
int V;
int rNode;
ll rDist;

void DFS(ll cDist, int nNode)
{
    if(rDist < cDist){
        rDist = cDist;
        rNode = nNode;
    }
    vst[nNode] = true;
    for(auto it : linkList[nNode]) {
        if(vst[it.first]) continue;
        DFS(cDist + it.second, it.first);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> V;
    for(int i = 0 ; i < V; i++)
    {
        int tmp1, tmp2;
        int order;
        cin >> order;
        while(1) {
            cin >> tmp1;
            if (tmp1 == -1) break;
            cin >> tmp2;
            linkList[order].push_back({tmp1, tmp2});
//            linkList[tmp1].push_back({order, tmp2});
        }
    }
    DFS(0, 1);
    rDist = 0;
    memset(vst, 0, V + 1);
    DFS(0, rNode);
    cout << rDist << "\n";
}
