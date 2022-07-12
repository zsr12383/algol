#include<bits/stdc++.h>
using namespace std;

struct Trie {
    int cnt = 0;
    map<char, Trie*> child;
};

map<char, Trie*> Start[2];

void makeTrie(string& str, int i) {
    if (!Start[i][str[0]])
        Start[i][str[0]] = new Trie();
    auto ptr = Start[i][str[0]];
    for (int i = 1; i < str.length(); i++)
    {
        if (!ptr->child[str[i]])
            ptr->child[str[i]] = new Trie();
        ptr = ptr->child[str[i]];
    }
}

int getCnt2(Trie *T)
{
    if (T->child.empty()) return 1;
    for (auto &it : T->child)
        T->cnt += getCnt2(it.second);
    return T->cnt;
}

void getCnt()
{
    for (int i = 0; i < 1; i++)
    {
        for (auto& it : Start[i])
            getCnt2(it.second);
    }
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;

    for (auto it : words)
    {
        makeTrie(it, 0);
        makeTrie(it, 1);
    }

    getCnt();

    for (auto it : queries)
    {
        bool flag = it[0] == '?';
        int beg = flag ? it.length() - 1 : 0;
        int ad = flag ? -1 : 1;
        auto ptr = Start[flag][it[beg]];
        if (!ptr) {
            answer.push_back(0);
            continue;
        }
        int i;
        int cnt;
        for (i = beg + ad; it[i] != '?'; i += ad)
        {
            if (!ptr->child[it[i]])
                break;
            cnt = ptr->cnt;
            ptr = ptr->child[it[i]];
        }
        if (it[i] == '?')
            answer.push_back(cnt);
        else
            answer.push_back(0);
    }


    return answer;
}

int main()
{
    solution({ "frodo", "front", "frost", "frozen", "frame", "kakao" }, { "fro??", "????o", "fr???", "fro???", "pro?" });
}