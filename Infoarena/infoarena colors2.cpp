#include <bits/stdc++.h>

using namespace std;

const int MAXM = 25e4 + 7;

vector<int> adj[MAXM];
int a[MAXM], b[MAXM];
pair<int, int> p[2 * MAXM];
int n, m;

int par[MAXM], sz[MAXM];
short ok[MAXM];

int find_par(int x){
	if(x == par[x]){
		return x;
	}

	return find_par(par[x]);
}

bool unite(int u, int v){
	//cout << "unite " << u << " " << v << "\n";
	if(find_par(u) == find_par(v)){
		return false;
	}

	if(sz[par[u]] < sz[par[v]]){
		swap(u, v);
	}

	sz[par[u]] += sz[par[v]];
	ok[par[u]] = max(ok[par[u]], ok[par[v]]);
	par[par[v]] = par[u];

	return true;
}

bool check(int l, int r){
	for(int i = l; i <= r; ++i){
		int u;
		if(p[i].second < 0){
			u = -p[i].second;
			ok[find_par(u)] = 2;
		}
		else{
			u = p[i].second;
			ok[find_par(u)] = max(ok[find_par(u)], (short)1);
			for(int to: adj[u]){
				if(ok[find_par(to)]){
					unite(u, to);
				}
			}
		}
	}

	for(int i = l; i <= r; ++i){
		if(p[i].second > 0){
			if(ok[ find_par(p[i].second) ] != 2){
				cout << l << " " << r << "false\n";
				return false;
			}
		}
	}

	for(int i = l; i <= r; ++i){
		ok[ find_par(abs(p[i].second)) ] = min(ok[ find_par(abs(p[i].second)) ], (short)1);
	}

	//cout << l << " " << r << "true\n";
	return true;
}

void solve(){
	cin >> n >> m;

	for(int i = 1; i <= n; ++i){
		cin >> a[i];
		p[i - 1] = {a[i], -i};
	}
	for(int i = 1; i <= n; ++i){
		cin >> b[i];
		p[i - 1 + n] = {b[i], i};
	}
	for(int i = 1; i <= n; ++i){
		adj[i].clear();
	}

	for(int i = 1; i <= m; ++i){
		int u, v;

		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 1; i <= n; ++i){
		if(a[i] < b[i]){
			cout << "0\n";
			return;
		}
	}

	for(int i = 1; i <= n; ++i){
		par[i] = i;
		ok[i] = 0;
		sz[i] = 1;
	}

	int start = 0;
	sort(p, p + 2 * n);
	for(int i = 1; i < 2 * n; ++i){
		if(p[i].first != p[i - 1].first){
			if(!check(start, i - 1)){
				cout << "0\n";
				return;
			}
			start = i;
		}
	}
	if(start != 2 * n){
		if(!check(start, 2 * n - 1)){
			cout << "0\n";
			return;
		}
	}

	cout << "1\n";

	return ;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//freopen("colors2.in", "r", stdin);
	//freopen("colors2.out", "w", stdout);

	int t;

	cin >> t;

	while(t--){
		solve();
	}

	return 0;
}