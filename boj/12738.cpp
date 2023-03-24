#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG
int A[1000000];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> tmp;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    tmp.emplace_back(A[0]);
    int cnt = 1;
    for (int i = 1; i < N; i++)
    {
        if (A[i] > tmp.back())
        {
            tmp.emplace_back(A[i]);
            cnt++;
        }
        else
            tmp[lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin()] = A[i];
    }
    cout << cnt;
}
