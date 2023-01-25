#include<stdio.h>

const int N=2e5+5;
int T,n,x,t,p[N];

int main() {
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        for (int i=1; i<=n; ++i)
            scanf("%d",&x),p[x]=i;
        t=(n>>1);
        while (t&&p[t]<=p[t+1]&&p[n+1-t]>=p[n-t]) --t;
        printf("%d\n",t);
    }
    return 0;
}
//https://codeforces.com/problemset/problem/1792/C