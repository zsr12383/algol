#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int N, K;
int cnt, lev;

deque<int> belt;
deque<int> up;
deque<int> down;

void rotate()
{
    down.push_front(up.back());
    up.pop_back();
    up.push_front(down.back());
    down.pop_back();

    for (auto& it : belt)
        it++;
    if (belt.size() && belt.back() == N - 1)
        belt.pop_back();
    lev++;
}

void move()
{
    for (int i = belt.size() - 1; i >= 0; i--)
    {
        if (up[belt[i] + 1] && ( i == belt.size() - 1 ||  belt[i] + 1 != belt[i + 1] ))
        {
            belt[i]++;
            up[belt[i]]--;
            if (up[belt[i]] == 0)
                cnt++;
        }
    }
    if (belt.size() && belt.back() == N - 1)
        belt.pop_back();
}

void raise()
{
    if (!up[0]) return;
    up[0]--;
    if (!up[0]) cnt++;
    belt.push_front(0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> K;
    up.resize(N);
    down.resize(N);

    for (int i = 0; i < N; i++)
        cin >> up[i];
    for (int i = 0; i < N; i++)
        cin >> down[i];
    cnt = 0;

    while (cnt < K)
    {
        rotate();
        move();
        raise();
    }
    cout << lev;
}
