#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
#define SIZE 20
#define INF (int)1e9

int R, C, ans; char MAP[SIZE + 2][SIZE + 2];
int check[SIZE + 2][SIZE + 2];
int ord[10]; int chk[10];
int graph[11][11]; int visit[11];
int path[11];

bool inRange(int r, int c) {
	return r >= 0 && c >= 0 && r < R&& c < C;
}

struct Info {
	int r, c, dist;
};

struct trash {
	pii pos;
	int dist; // 이건 시작점과 거리
};

Info s;
vector<trash> dirty;

void init() {
	memset(MAP, 0, sizeof(MAP));
	dirty.clear();
	ans = INF;
}

int bfs(Info st, pii en) { //갈수있다
	static int dr[4] = { -1, 1, 0, 0 };
	static int dc[4] = { 0, 0, -1, 1 };

	memset(check, 0, sizeof(check));
	queue<Info> q;
	check[st.r][st.c] = true; st.dist = 0;
	q.push(st);

	while (!q.empty()) {
		Info cur = q.front(); q.pop();
		if (cur.r == en.first && cur.c == en.second) {
			return cur.dist;
		}

		for (int d = 0; d < 4; d++) {
			int nR = cur.r + dr[d], nC = cur.c + dc[d];

			if (inRange(nR, nC) && !check[nR][nC] && MAP[nR][nC] != 'x') {
				check[nR][nC] = true;
				q.push({ nR, nC, cur.dist + 1 });
			}
		}
	}
	return INF; //못간다
}

bool cmp(const trash& a, const trash& b) {
	return a.dist < b.dist;
}

void dfs(int cur, int dist, int cnt) {
	if (dist > ans) return;
	if (cnt == dirty.size()) {
		ans = min(ans, dist);
		return;
	}
	//	visit[cur] = true;
	for (int next = 0; next < dirty.size(); next++) {
		if (cur == next) continue;
		//	if (visit[next]) continue;
		if (graph[cur][next] == INF) continue;

		if (visit[next] == false) {
			visit[next] = true;
			path[next] = cur;
			dfs(next, dist + graph[cur][next], cnt + 1);
			visit[next] = false;
		}
	}
}

void solve() {
	int st_node = dirty.size();
	//1. 시작점과의 거리를 구한다.
	for (int i = 0; i < dirty.size(); i++) {
		dirty[i].dist = bfs(s, dirty[i].pos);
		graph[st_node][i] = dirty[i].dist;
		graph[i][st_node] = dirty[i].dist;
	}

	sort(dirty.begin(), dirty.end(), cmp);

	if (dirty[0].dist == INF) {
		ans = INF;
		return;
	}

	//2. 인접 행렬 만들기
	for (int i = 0; i < st_node; i++) {
		for (int j = 0; j < st_node; j++) {
			if (i == j) continue;
			int dist = bfs({ dirty[i].pos.first, dirty[i].pos.second, 0 }, dirty[j].pos);
			graph[i][j] = graph[j][i] = dist;
		}
	}

	for (int i = 0; i < dirty.size(); i++) { //이부분 처리하지 않으면 맞왜틀
		if (dirty[i].dist == INF) continue;
		memset(visit, 0, sizeof(visit));
		visit[i] = true;
		dfs(i, dirty[i].dist, 1); //DFS 돌리기 전에 미리 시작점부터 거리를 저장
		visit[i] = false;
	}
}

int main() {
	//	freopen("1.txt", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0);

	while (true) {
		init();
		cin >> C >> R;
		if (R == 0 && C == 0) break;

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> MAP[i][j];
				switch (MAP[i][j]) {
				case 'o':
					s.r = i, s.c = j, s.dist = 0;
					break;
				case '*':
					dirty.push_back({ make_pair(i, j), 0 });
					break;
				}
			}
		}

		//답 출력
		solve();
		if (ans == INF) cout << -1 << '\n';
		else cout << ans << '\n';
	}

	return 0;
}
