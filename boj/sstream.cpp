#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string str = "2022   05 15";
    int tmp;
    stringstream st(str);

    while (st >> tmp)
        cout << tmp << endl;

    return 0;
}
