#include <bits/stdc++.h>
#include "split.h"

using namespace std;

const int MAXN = 2e5 + 7;

int n, a, b, c;
int num_a, num_b, num_c;
vector<int> p, q;
vector<int> adj[MAXN];
bool used[MAXN];
int sz[MAXN], par[MAXN];
vector<int> ans;

int dfs(int u){
	if(u == 0)
		par[u] = -1;

	used[u] = true;
	sz[u] = 1;

	int ret = -1;
	for(int to: adj[u]){
		if(used[to])
			continue;

		par[to] = u;
		int curr = dfs(to);
		sz[u] += sz[to];

		if(ret == -1)
			ret = curr;
	}

	if(ret == -1 && sz[u] >= a)
		ret = u;

	return ret;
}

int dfs_fill(int u, int nodes, int color){
	if(!nodes)
		return 0;

	used[u] = true;
	--nodes;
	ans[u] = color;

	for(int to: adj[u]){
		if(used[to])
			continue;

		nodes = dfs_fill(to, nodes, color);
	}

	return nodes;
}

vector<int> find_split(int _n, int _a, int _b, int _c, vector<int> _p, vector<int> _q) {
	n = _n, a = _a, b = _b, c = _c, p = _p, q = _q;
	num_a = 1;
	num_b = 2;
	num_c = 3;

	if(a > b){
		swap(a, b);
		swap(num_a, num_b);
	}
	if(a > c){
		swap(a, c);
		swap(num_a, num_c);
	}
	if(b > c){
		swap(b, c);
		swap(num_b, num_c);
	}
	ans.resize(n, 0);

	for(int i = 0; i < (int)p.size(); ++i){
		int u = p[i], v = q[i];

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int u = dfs(0);

	if(n - sz[u] < a)
		return vector<int>(n, 0);

	for(int i = 0; i < n; ++i)
		used[i] = false;

	if(n - sz[u] > sz[u]){
		used[u] = true;
		dfs_fill(par[u], b, num_b);
		used[u] = false;
		used[par[u]] = true;
		dfs_fill(u, a, num_a);
	}
	else{
		used[u] = true;
		dfs_fill(par[u], a, num_a);
		used[u] = false;
		used[par[u]] = true;
		dfs_fill(u, b, num_b);
	}

	for(int &val: ans){
		if(val == 0)
			val = num_c;
	}

	return ans;
}
