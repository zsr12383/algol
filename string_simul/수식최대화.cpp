#include<bits/stdc++.h>
using namespace std;
long long answer = 0;
string dSTR[] = {"*", "+", "-"};

auto mul = [](long long a, long long b){return a * b;};
auto add = [](long long a, long long b){return a + b;};
auto sub = [](long long a, long long b){return a - b;};

function<long long (long long, long long)> func[] = {mul, add, sub};

void dfs(int select, vector<string>& V){
    if(select == 7){
        answer = max(answer, abs(stoll(V[0])));
        return;
    }
    for(int i = 0 ; i < 3; i++){
        if((1 << i) & select) continue;
        vector<string> tmp;
        for(int j = 0 ; j < V.size(); j++){
            if(V[j] == dSTR[i]){
                long long l = stoll(tmp.back());
                tmp.pop_back();
                long long answer = func[i](l, stoll(V[j + 1]));
                tmp.push_back(to_string(answer));
                j++;
                continue;
            }
            tmp.push_back(V[j]);
        }
        dfs(select | (1 << i), tmp);
    }
    
}

long long solution(string expression) {
    vector<string> V;
    string buffer = "";
    for(auto c : expression){
        if(c == '+' || c == '-' || c == '*'){
            V.push_back(buffer);
            buffer = "";
            V.push_back(buffer + c);
            continue;
        }
        buffer += c;
    }
    if(!buffer.empty()) V.push_back(buffer);
    dfs(0, V);
    return answer;
}