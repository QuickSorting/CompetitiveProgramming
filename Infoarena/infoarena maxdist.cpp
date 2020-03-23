#include <bits/stdc++.h>

using namespace std;

const int kN = 2e5 + 7;
const int kLogN = 20;

int n, q;
vector<int> adj[kN];

class Solution{
private:
	static int depth[kN], up[kN][kLogN];
public:
	static void init_lca(int u, int parent){
		depth[u] = (parent == u) ? 0 : depth[parent] + 1;

		up[u][0] = parent;
		for(int i = 1; i < kLogN; ++i)
			up[u][i] = up[up[u][i - 1]][i - 1];

		for(int to: adj[u]){
			if(to == parent)
				continue;

			init_lca(to, u);
		}
	}

	static int get_lca(int u, int v){
		if(depth[u] != depth[v]){
			if(depth[u] < depth[v])
				swap(u, v);

			int diff = depth[u] - depth[v];
			for(int bit = kLogN - 1; bit >= 0; --bit)
				if(diff & (1 << bit))
					u = up[u][bit];
		}

		if(u == v)
			return u;

		for(int bit = kLogN - 1; bit >= 0; --bit){
			if(up[u][bit] != up[v][bit]){
				u = up[u][bit];
				v = up[v][bit];
			}
		}

		return up[u][0];
	}

	static int get_dist(int u, int v){
		return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
	}

private:
	int a, b, diameter;
public:
	Solution(){
		diameter = 0;
		a = -1;
		b = -1;
	}

	void add_node(int u){
		if(b == -1){
			if(a == -1)
				a = u;
			else{
				b = u;
				diameter = get_dist(a, b);
			}
			return;
		}

		int d1 = get_dist(u, a);
		int d2 = get_dist(u, b);

		if(d1 > d2 && d1 > diameter){
			diameter = d1;
			b = u;
		}
		if(d2 > d1 && d2 > diameter){
			diameter = d2;
			a = u;
		}
	}

	int get_diameter(){
		return diameter;
	}
};
int Solution::depth[kN], Solution::up[kN][kLogN]; 

int queries[kN], ans[kN][2];
bool vis[kN];
Solution sol[2];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("maxdist.in", "r", stdin);
	freopen("maxdist.out", "w", stdout);

	cin >> n >> q;
	for(int i = 0; i < n - 1; ++i){
		int u, v;
		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	Solution::init_lca(1, 1);

	for(int i = 0; i < q; ++i){
		cin >> queries[i];
		vis[queries[i]] = true;

		sol[1].add_node(queries[i]);
		ans[i][1] = sol[1].get_diameter();
	}

	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			sol[0].add_node(i);

	for(int i = q - 1; i >= 0; --i){
		ans[i][0] = sol[0].get_diameter();
		sol[0].add_node(queries[i]);
	}

	for(int i = 0; i < q; ++i)
		cout << ans[i][0] << " " << ans[i][1] << "\n";
}
/*
3 3
1 2
2 3
1
2
3
*/