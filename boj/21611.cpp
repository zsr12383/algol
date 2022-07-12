#include<bits/stdc++.h>
using namespace std;
int dr[] = { 0, 1, 0, -1 };
int dc[] = { -1, 0, 1, 0 };
pair<int, int> order[100];
vector<int> arr;
int N, M, ans;
int mp[50][50];
void readmp()
{
    int curR = (N + 1) / 2;
    int curC = (N + 1) / 2;
    int dir = 0;
    int leng = 0;
    bool cond = true;
    while(cond){
        if ((dir & 1) == 0) leng++;
        dir %= 4;
        for (int i = 0; i < leng; i++)
        {
            curR += dr[dir];
            curC += dc[dir];
            if (curC == 0 || !mp[curR][curC]) {
                cond = false;
                break;
            }
            arr.push_back(mp[curR][curC]);
        }
        dir++;
    }
}
void explo()
{
    bool cond = true;
    while (cond)
    {
        vector<int> tmp;
        cond = false;
        int left = 0, right = 0;
        while (right < arr.size())
        {
            int zerocnt = 0;
            while (right < arr.size() && (arr[left] == arr[right] || arr[right] == 0))
            {
                if (arr[right] == 0)
                    zerocnt++;
                right++;
            }
            int cnt = right - left - zerocnt;
            if (cnt >= 4) {
                ans += cnt * arr[left];
                left = right;
                cond = true;
            }
            else {
                for (; left < right; left++)
                    if(arr[left])
                        tmp.push_back(arr[left]);
            }
        }
        arr = tmp;
    }
}
void div()
{
    vector<int> tmp;
    int left = 0, right = 0;
    while (right < arr.size() && tmp.size() <= N * N - 3)
    {
        while (right < arr.size() && arr[left] == arr[right])
            right++;
        int cnt = right - left;

        tmp.push_back(cnt);
        tmp.push_back(arr[left]);
        left = right;
    }
    arr = tmp;
}
int eval(int i, int n)
{
    int init = -2 + 2 * i;
    int sum = 7 + 2 * i;
    return init + sum * (n - 1) + 8 * (n - 2) * (n - 1) / 2;
}
int trans(int num)
{
    switch (num)
    {
        case 1:
            return 4;
        case 2:
            return 2;
        case 3:
            return 1;
        case 4:
            return 3;
    default:
        break;
    }
    return 0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> mp[i][j];
    for (int i = 0; i < M; i++)
        cin >> order[i].first >> order[i].second;
    readmp();
    for (int j = 0 ; j<M;j++)
    {
        int idx = trans(order[j].first);
        for (int i = 1; i <= order[j].second; i++)
            if(arr.size() > eval(idx, i))
                arr[eval(idx, i)] = 0;
        explo();
        div();
    }
    cout << ans;
}
