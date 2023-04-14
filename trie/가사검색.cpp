#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;

struct Trie
{
	Trie* next[26];
	bool isFinal = false;
    unordered_map<int, int> mp;

	void insert(string& str, int idx)
	{
		if (idx == str.size())
		{
			isFinal = true;
			return;
		}
        mp[str.size() - idx]++;
		if(next[str[idx] - 'a'] == nullptr) next[str[idx] - 'a'] = new Trie();
		next[str[idx] - 'a']->insert(str, idx + 1);
	}

	int find(string& str, int idx)
	{
		if (idx == str.size())
		{
			if (isFinal) return 1;
			return 0;
		}
		if (str[idx] == '?') return mp[str.size() - idx];
		if (next[str[idx] - 'a'] == nullptr) return 0;
		return next[str[idx] - 'a']->find(str, idx + 1);
	}
};

vector<int> solution(vector<string> words, vector<string> queries)
{
	vector<int> answer;
	Trie* T = new Trie();
    Trie* rT = new Trie();
	for (auto& word : words){
		T->insert(word, 0);
        reverse(word.begin(), word.end());
        rT->insert(word, 0);
    }
	for (auto& query : queries){
        if(query[0] == '?'){
            reverse(query.begin(), query.end());
            answer.push_back(rT->find(query, 0));
            continue;
        }
		answer.push_back(T->find(query, 0));
    }
	return answer;
}