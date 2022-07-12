#include <bits/stdc++.h>
using namespace std;

vector <pair <int, int>> mat;
long long cnt[500][500];

int main()
{
    int n;
    scanf("%d", &n);
    mat.resize(n);
    for (int i = 0; i < n; i++)
    {
        int tmp1, tmp2;
        scanf("%d %d", &mat[i].first, &mat[i].second);
        cnt[i][i] = 0;
    }

    for (int diag = 1; diag <= n - 1; diag++)
        for (int i = 0; i < n - diag; i++)
        {
            int j = i + diag;
            long long min = LLONG_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                long long tmp = cnt[i][k] + cnt[k + 1][j] + mat[i].first * mat[j].second * mat[k].second;
                if (min > tmp)  // A          // (BCDE)에 대한 미리 구해둔 연산 수                  (A * BCDE)
                    min = tmp;
            }
            cnt[i][j] = min;
        }
    printf("%lld", cnt[0][n - 1]);
}

// (AB) + (CDE)// A + BCDE //
// A / BCDE
// AB CDE
// ABC DE
// ABCD E
// ABCDE
// i j 
// cnt[A][E] = cnt k

//                   0 0 0 0 0
//                   0 0 0 0 0
//                   0 0 0 0 0
//                   0 0 0 0 0
//                   0 0 0 0 0
//
