/*
	-Heavy-light decomposition
	-Had a bug which caused a time limit because i type kMaxN instead of kMaxLogN
*/
#include <bits/stdc++.h>

using namespace std;
void read();

const int kMaxN = 2e4 + 7;
const int kMaxLogN = 15;

inline int fmax(int a, int b){
	return ((a > b) ? a : b);
}

inline int fmin(int a, int b){
	return ((a < b) ? a : b);
}

struct SegmentTree{
	int nodes[4 * kMaxN];

	SegmentTree(){}

	void clear(){
	}

	void build(int idx, int l, int r, const int arr[]){
		if(l == r){
			nodes[idx] = arr[l];
			return;
		}

		int mid = (l + r) >> 1;
		build((idx << 1), l, mid, arr);
		build((idx << 1) + 1, mid + 1, r, arr);

		nodes[idx] = fmax(nodes[(idx << 1)], nodes[(idx << 1) + 1]);
	}

	void update(int idx, int l, int r, int s, int val){
		if(s < l || r < s)
			return;
		if(l == r){
			nodes[idx] = val;
			return;
		}

		int mid = (l + r) >> 1;
		update((idx << 1), l, mid, s, val);
		update((idx << 1) + 1, mid + 1, r, s, val);

		nodes[idx] = fmax(nodes[(idx << 1)], nodes[(idx << 1) + 1]);
	}

	int query(int idx, int l, int r, int sl, int sr){
		if(sr < l || r < sl)
			return 0;
		if(sl <= l && r <= sr)
			return nodes[idx];

		int mid = (l + r) >> 1;
		int lvalue = query((idx << 1), l, mid, sl, sr);
		int rvalue = query((idx << 1) + 1, mid + 1, r, sl, sr);

		return fmax(lvalue, rvalue);
	}
};

int n;
//vector<array<int, 3>> queries;
vector<pair<int, int>> adj[kMaxN];
int tr_sz[kMaxN], up[kMaxN][kMaxLogN], depth[kMaxN];
int head[kMaxN], start[kMaxN], dfs_time;
array<int, 3> edges[kMaxN];
SegmentTree seg_tr;

int arr[kMaxN];

void pre_dfs(int u, int par){
	if(par == u)
		depth[u] = 0;
	else
		depth[u] = depth[par] + 1;

	tr_sz[u] = 1;

	up[u][0] = par;
	for(int i = 1; i < kMaxLogN; ++i)
		up[u][i] = up[up[u][i - 1]][i - 1];

	for(auto edge: adj[u]){
		int to = edge.first, w = edge.second;
		if(to == par)
			continue;

		pre_dfs(to, u);
		tr_sz[u] += tr_sz[to];
	}
}

int get_lca(int u, int v){
	if(depth[u] != depth[v]){
		if(depth[u] < depth[v])
			swap(u, v);

		int diff = depth[u] - depth[v];
		for(int i = 0; i < kMaxLogN && diff; ++i){
			if(diff & (1 << i)){
				u = up[u][i];
				diff ^= (1 << i);
			}
		}
	}

	if(u == v)
		return u;

	for(int i = kMaxLogN - 1; i >= 0 && up[u][0] != up[v][0]; --i){
		if(up[u][i] != up[v][i]){
			u = up[u][i];
			v = up[v][i];
		}
	}

	return up[u][0];
}

void decompose(int u, int par, int head_, int par_w){
	head[u] = head_;
	start[u] = ++dfs_time;
	//seg_tr.update(1, 1, n, start[u], par_w);
	arr[start[u]] = par_w;

	int mx_sz = -1, heavy = -1, hw = -1;
	for(auto edge: adj[u]){
		int to = edge.first, w = edge.second;
		if(to == par)
			continue;

		if(tr_sz[to] > mx_sz){
			mx_sz = tr_sz[to];
			heavy = to;
			hw = w;
		} 
	}

	if(mx_sz != -1)
		decompose(heavy, u, head_, hw);

	for(auto edge: adj[u]){
		int to = edge.first, w = edge.second;
		if(to == par || to == heavy)
			continue;

		decompose(to, u, to, w);
	}
}

void hld_precompute(){
	dfs_time = 0;
	pre_dfs(1, 1);
	decompose(1, 1, 1, 0);
	seg_tr.build(1, 1, n, arr);
}

int get_path_up(int u, int anc){
	int ret = 0;
	while(start[anc] < start[u]){
		int curr = seg_tr.query(1, 1, n, fmax(start[anc] + 1, start[head[u]]), start[u]);
		ret = fmax(ret, curr);
		u = up[head[u]][0];
	}

	return ret;
}

int get_max_in_path(int u, int v){
	int l = get_lca(u, v);
	int ret = 0;

	ret = fmax(ret, get_path_up(u, l));
	ret = fmax(ret, get_path_up(v, l));

	return ret;
}

char s[10];

void solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		adj[i].clear();

	for(int i = 0; i < n - 1; ++i){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		edges[i] = {a, b, c};
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	hld_precompute();
	scanf("%s", &s);

	while(s[0] != 'D'){
		array<int, 3> query;

		query[0] = (s[0] == 'Q');
		scanf("%d %d", &query[1], &query[2]);
		scanf("%s", &s);

		if(query[0] == 0){
			--query[1];
			auto edge = edges[query[1]];
			if(depth[edge[0]] > depth[edge[1]])
				seg_tr.update(1, 1, n, start[edge[0]], query[2]);
			else
				seg_tr.update(1, 1, n, start[edge[1]], query[2]);
		}
		else
			printf("%d\n", get_max_in_path(query[1], query[2]));
	}
}

int main(){
	int t;
	scanf("%d", &t);

	while(t--)
		solve();

	return 0;
}

/*
1

7
3 7 10
1 2 3
1 3 4
2 4 3
2 5 4
3 6 5
QUERY 1 1
QUERY 1 2 
QUERY 4 7
QUERY 3 5
QUERY 6 7
CHANGE 2 20
QUERY 1 1
QUERY 1 2 
QUERY 4 7
QUERY 3 5
QUERY 6 7
DONE
*/