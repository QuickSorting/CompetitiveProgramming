#include <bits/stdc++.h>

using namespace std;

struct point{
	int x, y;
	point(){}
	point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

inline int sq(int x){
	return x * x;
}

inline int find_distance(point a, point b){
	return sq(a.x - b.x) + sq(a.y - b.y);
}

const int kMaxN = 1007;
const int inf = 1e9 + 7;
bool used[kMaxN][kMaxN];
int dist[kMaxN][kMaxN];
int n, m;

bool dfs(point start, point end, int mid){
	if(dist[start.x][start.y] < mid)
		return false;
	if(start.x == end.x && start.y == end.y)
		return true;

	used[start.x][start.y] = true;

	array<point, 4> adj = {point(start.x + 1, start.y), point(start.x - 1, start.y), point(start.x, start.y + 1), point(start.x, start.y - 1)};
	for(point to: adj){
		if(to.x < 1 || to.y < 1 || to.x > n || to.y > m)
			continue;
		if(used[to.x][to.y])
			continue;
		
		if(dfs(to, end, mid))
			return true;
	}

	return false;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	point start, end;
	cin >> start.x >> start.y >> end.x >> end.y;

	int cnt_frogs;
	cin >> cnt_frogs;

	priority_queue<array<int, 4>, vector<array<int, 4>>, greater<array<int, 4>>> pq;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			dist[i][j] = inf;
		}
	}

	vector<point> frogs;
	for(int i = 0; i < cnt_frogs; ++i){
		int x, y;
		cin >> x >> y;
		frogs.push_back(point(x, y));
	}

	if(cnt_frogs > 50){
		for(int i = 0; i < cnt_frogs; ++i){
			int x = frogs[i].x;
			int y = frogs[i].y;
			pq.push({0, i, x, y});
			dist[x][y] = 0;
		}

		while(!pq.empty()){
			array<int, 4> node = pq.top();
			pq.pop();

			point p(node[2], node[3]), origin = frogs[node[1]];
			if(used[p.x][p.y])
				continue;
			used[p.x][p.y] = true;

			array<point, 8> adj;
			int cnt = 0;
			for(int x = -1; x <= 1; ++x){
				for(int y = - 1; y <= 1; ++y){
					if(x == 0 && y == 0)
						continue;
					adj[cnt++] = point(p.x + x, p.y + y);
				}
			}

			for(point to: adj){
				if(to.x < 1 || to.y < 1 || to.x > n || to.y > m)
					continue;

				int curr = find_distance(to, origin);
				if(dist[to.x][to.y] > curr){
					dist[to.x][to.y] = curr;
					pq.push({curr, node[1], to.x, to.y});
				}
			}
		}
	}
	else{
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= m; ++j){
				dist[i][j] = inf;
				for(point frog: frogs)
					dist[i][j] = min(find_distance(frog, point(i, j)), dist[i][j]);
			}
		}
	}

	int l = 0, r = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			r = max(r, dist[i][j]);

	while(l != r){
		int mid = (l + r + 1) >> 1;

		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				used[i][j] = false;

		if(dfs(start, end, mid))
			l = mid;
		else
			r = mid - 1;
	}

	cout << l << "\n";
	return 0;
}