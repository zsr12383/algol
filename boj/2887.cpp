#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int N;

struct Pos{
    int x, y, z;
};

Pos P[100000];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i = 0 ; i < N;i++){
        cin >> P[i].x >> P[i].y >> P[i].z;
    }

}
