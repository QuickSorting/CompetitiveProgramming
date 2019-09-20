/*
	I run a BFS from a single node and i get the longest distance from it.Then say the diameter is from u to v.Then the diameter will
be at most the distance d(u, first node) + d(v, first node) because this is a possible path. But we know that this both of these 
distances are smaller or equal to the longest distance from the first node. That means the actual diameter will be at most
2 * (longest distance from first node). Because the answer is log(diameter - 1) + 1, that means the actual answer will be at most
one bigger than the answer we will get with the longest path we got. So this is a good enough answer.

*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 41007;

vector<int> adj[MAXN];
bool used[MAXN];
int dist[MAXN];

int bfs(int u){
	queue<int> q;

	q.push(u);
	dist[u] = 0;
	used[u] = true;

	int ret = 0;
	while(!q.empty()){
		u = q.front();
		q.pop();

		ret = dist[u];

		for(int to: adj[u]){
			if(!used[to]){
				dist[to] = dist[u] + 1;
				used[to] = true;
				q.push(to);
			}
		}
	}

	return ret;
}

void solve(){
	int n, m;

	cin >> n >> m;

	for(int i = 1; i <= n; ++i){
		used[i] = false;
		adj[i].clear();
	}
	
	for(int i = 0; i < m; ++i){
		int x, y;

		cin >> x >> y;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	int diameter = bfs(1);

	if(diameter <= 1){
		cout << "0\n";
		return;
	}

	//cout << diameter << " diameter" << endl;

	cout << (int)log2((int)diameter - 1) + 1 << "\n";

	return;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("amici2.in", "r", stdin);
	freopen("amici2.out", "w", stdout);

	int t;

	cin >> t;

	while(t--){
		solve();
	}

	return 0;
}