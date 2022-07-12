#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

//S => 1, N => 0

int gearRidx[5] = {0, 2, 2, 2, 2 };
int direct[5] = { 0, 0, 0, 0, 0 };
int gear[5][8];
int K;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    for (int i = 1; i <= 4; i++)
    {
        int tmp;
        cin >> tmp;
        for (int j = 7; j >= 0; j--)
        {
            gear[i][j] = tmp % 10;
            tmp /= 10;
        }
    }

    cin >> K; 

    while (K--)
    {
        int order;
        cin >> order;
        memset(direct, 0, sizeof(direct));
        cin >> direct[order];

        for (int i = order + 1; i <= 4; i++)
        {
            if (gear[i][(gearRidx[i] + 4) % 8] == gear[i - 1][gearRidx[i - 1]]) continue;
            direct[i] = -direct[i - 1];
        }

        for (int i = order - 1; i >= 1; i--)
        {
            if (gear[i + 1][(gearRidx[i + 1] + 4) % 8] == gear[i][gearRidx[i]]) continue;
            direct[i] = -direct[i + 1];
        }

        for (int i = 1; i <= 4; i++)
        {
            switch (direct[i])
            {
            case 1:
                gearRidx[i] += 6;
            case -1:
                gearRidx[i]++;
            default:
                gearRidx[i] %= 8;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= 4; i++)
        if (gear[i][(gearRidx[i] + 6) % 8] == 1)
            ans += 1 << (i - 1);
    cout << ans;
}



