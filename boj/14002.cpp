#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int A[1000];
int length[1000];
int N;
deque<int> anss;

int LIS(int n) {
    int ret = 1001;
    int padd;
    for (int k = 1; k < n; k++) {
        length[k] = 1;
        for (int i = 0; i < k; i++) {
            if (A[i] < A[k]) {
                if (length[k] < length[i] + 1) {
                    length[k] = length[i] + 1;
                    ret = i;
                    padd = k;
                }
            }
        }
    }
    if (ret != 1001)
        anss.push_front(A[padd]);
    else {
        if (n == N) anss.push_front(A[n - 1]);
        else anss.push_front(A[n]);
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    if (N >= 2) {
        int tmp = LIS(N);
        while (tmp != 1001) {
            tmp = LIS(tmp);
        }
    }
    else
        anss.push_back(A[0]);
    cout << anss.size() << "\n";
    for (auto it : anss)
        cout << it << " ";
}
