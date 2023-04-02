#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define DEBUG

map<string, int> friendCount;
map<string, string> parent;
int T, F;
string A, B;

void InitMember(string S)
{
	if (parent.find(S) != parent.end()) return;
	parent[S] = S;
	friendCount[S] = 1;
}

string FindRoot(string S)
{
	if (S == parent[S]) return S;
	parent[S] = FindRoot(parent[S]);
	return parent[S];
}

void swapStr(string &s1, string &s2)
{
	if(s1 > s2)
	{
		string tmp = s1;
		s1 = s2;
		s2 = tmp;
	}
}

int UnionFind(string s1, string s2)
{
	string s1Root = FindRoot(s1);
	string s2Root = FindRoot(s2);
	if (s1Root == s2Root) return friendCount[s1Root];
	swapStr(s1Root, s2Root);
	parent[s2Root] = s1Root;
	friendCount[s1Root] += friendCount[s2Root];
	return friendCount[s1Root];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> T;
	while(T--)
	{
		cin >> F;
		friendCount.clear();
		parent.clear();
		while(F--)
		{
			cin >> A >> B;
			InitMember(A);
			InitMember(B);
			cout << UnionFind(A, B) << "\n";
		}
	}
}
