#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug

int N;
bool arr[1001];

void init(){
    arr[1] = true;
    arr[2] = false;
    arr[3] = true;
    for(int i = 4 ; i <1001;i++){
        if(arr[i - 1] == false && arr[i - 3] == false)
            arr[i] = true;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    init();
    if(arr[N]) cout << "SK\n";
    else cout << "CY\n";
}

// 1개 내가 가져감 (윈) -> 2개, 4개 (상대승)
// 3개 내가 가져감 (윈) -> 4개, 6개 (상대승)

