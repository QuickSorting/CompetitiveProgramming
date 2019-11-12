/*
	Followed the tutorial
*/
#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 2007;
const long long inf = 1e18;

struct edge{
	long long to, w;

	edge(){}
	edge(long long to, long long w){
		this->to = to;
		this->w = w;
	}
};

struct state{
	long long u, d;

	state(){}
	state(long long u, long long d){
		this->u = u;
		this->d = d;
	}

	friend bool operator<(const state &lvalue, const state &rvalue){
		return lvalue.d > rvalue.d;
	}
};

long long n, m, a, b, k;
long long dist[MAXN], dist_b[MAXN], par[MAXN], idx_in_path[MAXN];
long long lca[MAXN], depth[MAXN], pr[MAXN], ans[MAXN];
bool used[MAXN];
vector<edge> adj[MAXN];
vector<long long> path, adj_d[MAXN];
vector<array<long long, 3> > edges;

void dijkstra(int start){
	for(long long i = 1; i <= n; ++i){
		dist[i] = inf;
		used[i] = false;
	}

	priority_queue<state> pq;
	pq.push(state(start, 0));
	dist[start] = 0;
	par[start] = -1;

	while(!pq.empty()){
		state st = pq.top();
		pq.pop();

		long long u = st.u, d = st.d;
		if(used[u])
			continue;
		used[u] = true;

		for(edge e: adj[u]){
			long long to = e.to, w = e.w;
			pair<long long, long long> p = {u, to};
			if(used[to])
				continue;
			if(start == a){
				if(d + w < dist[to] && (idx_in_path[to] <= 0 || path[idx_in_path[to] - 1] == u)){
					dist[to] = d + w;
					par[to] = u;
					pq.push(state(to, dist[to]));
				}
			}
			else{
				if(d + w < dist[to]){
					dist[to] = d + w;
					par[to] = u;
					pq.push(state(to, dist[to]));
				}
			}
		}
	}
}

void find_depth(long long u, long long p = -1, long long curr_d = 0){
	depth[u] = curr_d++;
	for(long long to: adj_d[u]){
		if(to == p){
			continue;
		}
		find_depth(to, u, curr_d);
	}
}

long long get_lca(long long v){
	long long curr1 = v, curr2 = b;
	while(depth[curr1] != depth[curr2]){
		if(depth[curr1] < depth[curr2]){
			curr2 = par[curr2];
		}
		else{
			curr1 = par[curr1];
		}
	}
	while(curr1 != curr2){
		curr1 = par[curr1];
		curr2 = par[curr2];
	}

	return curr1;
}

void solve(){
	dijkstra(b);
	for(long long i = 1; i <= n; ++i){
		dist_b[i] = dist[i];
	}
	dijkstra(a);

	for(long long i = 1; i <= n; ++i){
		if(par[i] != -1){
			adj_d[par[i]].push_back(i);
			adj_d[i].push_back(par[i]);
		}
	}

	find_depth(a);
	for(long long i = 1; i <= n; ++i){
		lca[i] = get_lca(i);
	}

	for(long long i = 0; i < k; ++i){
		ans[i] = inf;
	}

	for(array<long long, 3> p: edges){
		long long u = p[0], v = p[1], w = p[2];
		if(par[u] == v || par[v] == u){
			continue;
		}

		long long idx1 = idx_in_path[lca[u]], idx2 = idx_in_path[lca[v]];
		if(idx1 > idx2){
			swap(idx1, idx2);
			swap(u, v);
		}

		for(int i = idx1; i < idx2; ++i){
			ans[i] = min(ans[i], dist[u] + dist_b[v] + w);
		}
	}
}

void write(){
	for(int i = 0; i < k - 1; ++i){
		if(ans[i] < inf){
			cout << ans[i] << "\n";
		}
		else{
			cout << "-1\n";
		}
	}
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> a >> b;
	for(long long i = 0; i < m; ++i){
		long long u, v, w;

		cin >> u >> v >> w;

		adj[u].push_back(edge(v, w));
		adj[v].push_back(edge(u, w));
		edges.push_back({u, v, w});
	}

	cin >> k;
	for(long long i = 1; i <= n; ++i){
		idx_in_path[i] = -1;
	}
	for(long long i = 0; i < k; ++i){
		long long u;
		cin >> u;
		idx_in_path[u] = i;
		path.push_back(u);
	}
}

int main(){
	read();
	solve();
	write();
}
/*
6 7 1 6
1 2 1
2 3 1
3 4 1
4 5 1
2 5 2
3 6 2
2 6 7
4 1 2 3 6
*/