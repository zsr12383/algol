#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int N;
    priority_queue<int> q1;
    priority_queue<int, vector<int>, greater<int>> q2;

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int tmp;
        scanf("%d", &tmp);
        if (i % 2)
            q2.push(tmp);
        else
            q1.push(tmp);

        if (i >= 1) {
            int q1top = q1.top();
            int q2top = q2.top();
            if (q1top > q2top) {
                q1.pop();
                q2.pop();
                q1.push(q2top);
                q2.push(q1top);
                printf("%d\n", q1.top());
            }
            else
                printf("%d\n", q1top);
        }
        else
            printf("%d\n", tmp);
    }
    return 0;
}