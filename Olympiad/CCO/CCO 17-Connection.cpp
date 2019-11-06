/*
	Followed the tutorial
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 7;

int n, d, q;
array<int, 2> edge[MAXN], quer[MAXN];
int par[MAXN], dsu_2ecc[MAXN], dsu_cc[MAXN], dsu_cc_size[MAXN];
int bridges, lca_iteration, last_visit[MAXN];

int l[MAXN], r[MAXN], ans[MAXN];
vector<int> v[MAXN];

void init(){
	lca_iteration = 0;
	for(int i = 0; i < n + 1; ++i){
		last_visit[i] = 0;
		dsu_2ecc[i] = i;
		dsu_cc[i] = i;
		dsu_cc_size[i] = 1;
		par[i] = -1;
	}
	bridges = 0;

	for(int i = 0; i < d; ++i){
		v[i].clear();
	}
}

int find_2ecc(int v){
	if(v == -1)
		return v;
	if(dsu_2ecc[v] == v)
		return v;
	return dsu_2ecc[v] = find_2ecc(dsu_2ecc[v]);
}

int find_cc(int v){
	v = find_2ecc(v);
	if(dsu_cc[v] == v)
		return v;
	return dsu_cc[v] = find_cc(dsu_cc[v]);
}

void make_root(int v){
	v = find_2ecc(v);
	int root = v;
	int child = -1;
	while(v != -1){
		int p = find_2ecc(par[v]);
		par[v] = child;
		dsu_cc[v] = root;
		child = v;
		v = p;
	}
	dsu_cc_size[root] = dsu_cc_size[child];
}

void merge_path(int a, int b){
	++lca_iteration;
	vector<int> path_a, path_b;
	int lca = -1;
	while(lca == -1){
		if(a != -1){
			a = find_2ecc(a);
			path_a.push_back(a);
			if(last_visit[a] == lca_iteration){
				lca = a;
				break;
			}
			last_visit[a] = lca_iteration;
			a = par[a];
		}
		if(b != -1){
			b = find_2ecc(b);
			path_b.push_back(b);
			if(last_visit[b] == lca_iteration){
				lca = b;
				break;
			}
			last_visit[b] = lca_iteration;
			b = par[b];
		}
	}

	for(int v: path_a){
		dsu_2ecc[v] = lca;
		if(v == lca)
			break;
		--bridges;
	}
	for(int v: path_b){
		dsu_2ecc[v] = lca;
		if(v == lca)
			break;
		--bridges;
	}
}

void add_edge(int a, int b){
	a = find_2ecc(a);
	b = find_2ecc(b);
	if(a == b)
		return;

	int ca = find_cc(a);
	int cb = find_cc(b);

	if(ca != cb){
		++bridges;
		if(dsu_cc_size[ca] > dsu_cc_size[cb]){
			swap(a, b);
			swap(ca, cb);
		}
		make_root(a);
		par[a] = dsu_cc[a] = b;
		dsu_cc_size[cb] += dsu_cc_size[ca];
	}
	else{
		merge_path(a, b);
	}
}


void solve(){
	for(int i = 0; i < q; ++i){
		l[i] = 0;
		r[i] = d - 1;
		ans[i] = -1;
	}

	for(int i = 0; i < 25; ++i){
		init();

		for(int j = 0; j < q; ++j){
			if(l[j] > r[j])
				continue;

			int mid = (l[j] + r[j]) >> 1;
			v[mid].push_back(j);
		}

		for(int j = 0; j < d; ++j){
			add_edge(edge[j][0], edge[j][1]);
			for(auto qq: v[j]){
				int u = quer[qq][0], v = quer[qq][1];

				if(find_2ecc(u) == find_2ecc(v)){
					ans[qq] = j;
					r[qq] = j - 1;
				}
				else{
					l[qq] = j + 1;
				}
			}
		}
	}
}

void write(){
	for(int i = 0; i < q; ++i){
		cout << ans[i] << "\n";
	}
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> d >> q;

	for(int i = 0; i < d; ++i){
		cin >> edge[i][0] >> edge[i][1];
	}
	for(int i = 0; i < q; ++i){
		cin >> quer[i][0] >> quer[i][1];
	}
}

int main(){
	read();
	solve();
	write();

	return 0;
}