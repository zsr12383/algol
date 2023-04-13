#include<bits/stdc++.h>
using namespace std;

map<string, string> uid_name;
vector<pair<string, string>> msgList; //uid, type
map<string, string> output;

vector<string> div_word(string& src)
{
    vector<string> str;
    int l = 0, r;
    for(r = 0; r<src.size();r++)
        if(src[r] == ' '){
            str.push_back(src.substr(l, r - l));
            l = r + 1;
        }
    str.push_back(src.substr(l));
    return str;
}

void init()
{
    output["Enter"] = "님이 들어왔습니다.";
    output["Leave"] = "님이 나갔습니다.";
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> mp;
    init();
    for(auto& it : record)
    {
        auto tmp = div_word(it);
        string types = tmp[0];
        string uid = tmp[1];
        string names = tmp.size() == 3 ? tmp[2] : "";
        
        if(types != "Leave"){
            uid_name[uid] = names;
        }
        if(types != "Change"){
            msgList.push_back(make_pair(uid, types));
        }
    }
    for(auto [uid, type] : msgList){
        answer.push_back(uid_name[uid] + output[type]);
    }
    return answer;
}