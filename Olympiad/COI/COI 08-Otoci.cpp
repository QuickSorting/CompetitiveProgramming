#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 3e4 + 7;
const int kMaxLogN = 17;
const int kMaxQ = 3e5 + 7;

struct Fenwick{
	int nodes[kMaxN];

	Fenwick(){
		for(int i = 0; i < kMaxN; ++i)
			nodes[i] = 0;
	}

	void update(int idx, int diff){
		for(; idx < kMaxN; idx += (idx & -idx))
			nodes[idx] += diff;
	}

	int query(int idx){
		int ret = 0;
		for(; idx >= 1; idx -= (idx & -idx))
			ret += nodes[idx];
		return ret;
	}

	int query(int l, int r){
		return query(r) - query(l - 1);
	}
};

void read();

Fenwick fenwick;

int n, q, a[kMaxN];
array<int, 3> queries[kMaxQ];
vector<int> adj[kMaxN];
int parent[kMaxN], size[kMaxN];
int up[kMaxN][kMaxLogN];
int depth[kMaxN], tr_sz[kMaxN];
bool used[kMaxN];

int find_parent(int u){
	return (parent[u] == u) ? u : (parent[u] = find_parent(parent[u])); 
}

bool unite(int u, int v){
	if(find_parent(u) == find_parent(v))
		return false;
	int pu = parent[u], pv = parent[v];
	if(size[pu] < size[pv]){
		swap(pu, pv);
		swap(u, v);
	}

	size[pu] += size[pv];
	parent[pv] = pu;

	return true;
}

void dfs(int u, int parent = -1){
	if(parent == -1){
		up[u][0] = u;
		depth[u] = 0;
	}
	else{
		up[u][0] = parent;
		depth[u] = depth[parent] + 1;
	}
	used[u] = true;
	tr_sz[u] = 1;

	for(int to: adj[u]){
		if(to == parent)
			continue;
		dfs(to, u);
		tr_sz[u] += tr_sz[to];
	}
}

void init_lca(){
	for(int i = 1; i <= n; ++i){
		if(!used[i])
			dfs(i, -1);
	}

	for(int j = 1; j < kMaxLogN; ++j){
		for(int i = 1; i <= n; ++i)
			up[i][j] = up[up[i][j - 1]][j - 1];
	}
}

int find_lca(int u, int v){
	if(u == v)
		return u;

	if(depth[u] < depth[v])
		swap(u, v);

	int diff = depth[u] - depth[v];
	for(int i = kMaxLogN - 1; i >= 0; --i){
		if(diff & (1 << i))
			u = up[u][i];
	}

	if(u == v){
		return u;
	}

	for(int i = kMaxLogN - 1; i >= 0; --i){
		if(up[u][i] != up[v][i]){
			u = up[u][i];
			v = up[v][i];
		}
	}

	return up[u][0];
}

void init_dsu(){
	for(int i = 1; i <= n; ++i){
		parent[i] = i;
		size[i] = 1;
	}
}

void find_adj(){
	for(int i = 1; i <= q; ++i){
		array<int, 3> query = queries[i];

		if(query[0] == 0 && unite(query[1], query[2])){
			adj[query[1]].push_back(query[2]);
			adj[query[2]].push_back(query[1]);
		}
	}
}

int head[kMaxN], st[kMaxN], en[kMaxN], dfs_time;

void decompose(int u, int pr, int head_){
	head[u] = head_;
	st[u] = ++dfs_time;
	fenwick.update(st[u], a[u]);
	used[u] = true;

	int mx_sz = -1, f_c = -1;
	for(int v: adj[u]){
		if(v != pr){
			if(mx_sz < tr_sz[v]){
				mx_sz = tr_sz[v];
				f_c = v;
			}
		}
	}

	if(f_c != -1)
		decompose(f_c, u, head_);

	for(int v: adj[u]){
		if(v != pr && v != f_c)
			decompose(v, u, v);
	}

	en[u] = dfs_time;
}

void hld_precompute(){
	for(int i = 1; i <= n; ++i)
		used[i] = false;
	for(int i = 1; i <= n; ++i){
		if(!used[i])
			decompose(i, i, i);
	}
}

vector<pair<int, int>> get_path_up(int u, int anc){
	vector<pair<int, int>> ret;
	while(st[anc] < st[u]){
		ret.push_back({max(st[anc] + 1, st[head[u]]), st[u]});
		u = up[head[u]][0];
	}

	return ret;
}

vector<pair<int, int>> get_path(int u, int v){
	int l = find_lca(u, v);
	vector<pair<int, int>> ret = get_path_up(u, l);


	//if we consider vertices, not edges
	ret.push_back({st[l], st[l]});

	vector<pair<int, int>> oth = get_path_up(v, l);
	reverse(oth.begin(), oth.end());

	//if the path is directed
	//for(auto &it: oth) swap(it.first, it.second);

	for(auto it: oth)
		ret.push_back(it);

	return ret;
}

int get_sum_on_path(int u, int v){
	vector<pair<int, int>> path = get_path(u, v);
	int ret = 0;

	for(pair<int, int> range: path)
		ret += fenwick.query(range.first, range.second);

	return ret;
}

void find_answer(){
	hld_precompute();

	for(int i = 1; i <= q; ++i){
		array<int, 3> query = queries[i];

		if(query[0] == 0){
			if(unite(query[1], query[2]))
				cout << "yes\n";
			else
				cout << "no\n";
			continue;
		}
		if(query[0] == 1){
			fenwick.update(st[query[1]], query[2] - a[query[1]]);
			a[query[1]] = query[2];
		}
		if(query[0] == 2){
			if(find_parent(query[1]) != find_parent(query[2])){
				cout << "impossible\n";
				continue;
			}

			cout << get_sum_on_path(query[1], query[2]) << "\n";
		}
	}
}

void solve(){
	init_dsu();
	find_adj();

	init_lca();
	init_dsu();
	find_answer();
}

int main(){
	read();
	solve();
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> q;
	for(int i = 1; i <= q; ++i){
		string type;
		cin >> type;

		if(type == "bridge")
			queries[i][0] = 0;
		else if(type == "penguins")
			queries[i][0] = 1;
		else if(type == "excursion")
			queries[i][0] = 2;

		cin >> queries[i][1] >> queries[i][2];
	}
}