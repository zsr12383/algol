#include <bits/stdc++.h>

//nlogn, 분할정복 좌, 우, 걸친 부분 3가지 case 탐색
int fastMaxSum(const vector<int> &A, int lo, int hi) {
    //기저 사례: 구간의 길이가 1일 경우
    if (lo == hi) return A[lo];

    int mid = (lo + hi) / 2;
    int left = INT_MIN, right = INT_MIN, sum = 0;

    // 끼인 부분 탐색
    for (int i = mid; i >= lo; --i) {
        sum += A[i];
        left = max(left, sum);
    }
    sum = 0;
    for (int i = mid + 1; i <= hi; ++i) {
        sum += A[i];
        right = max(right, sum);
    }

    int oneSide = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid + 1, hi));
    return max(left + right, oneSide);
}

//n, DP, A[i]를 오른쪽 끝으로 갖는 구간의 최대 합을 찾기
//A[i]가 최대가 되는 경우는 A[i]만 있거나, A[i-1]을 오른쪽 끝으로 갖는 최대 합 구간에 A[i]를 더하는 두가지 경우
int fastestMaxSum(const vector<int> &A) {
    int N = (int) A.size(), ret = INT_MIN, psum = 0;
    for (int i = 0; i < N; ++i) {
        psum = max(psum, 0) + A[i];
        ret = max(psum, ret);
    }
    return ret;
}