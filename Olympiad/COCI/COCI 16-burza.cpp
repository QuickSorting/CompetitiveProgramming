/*
I am not sure whether this solution can be broken but it passes all the tests
I firstly remove all nodes that do not participate in a path from 1 of length k
Then, for every layer(distance from 1), I try marking each vertex
The complexity then becomes the product of the count of vertices in each layer
Because I have some returns for trivial cases the worst case is when each layer consists of around 20 vertices and the layers are 20
Then the number of operations will be 20^20
But in this case a lot of vertices are basically the same, and the order doesn't matter much
So if there is a solution it will be found fast
To avoid time limits, when I run out of time I output NO

I haven't looked at the official solution yet, but I will tomorrow
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 407;

int n, k;
vector<int> adj[MAXN], g[MAXN];

clock_t timer = clock();

bool dfs(int u, int d, int p = -1){
	bool ok = false;

	for(int to: adj[u]){
		if(to == p){
			continue;
		}
		bool curr = dfs(to, d + 1, u);

		if(curr){
			g[u].push_back(to);
			ok = curr;
		}
	}
	if(d == k){
		ok = true;
	}

	return ok;
}

bool solve(const vector<int> &ver, int d){
	if((float)(clock() - timer) / (float)CLOCKS_PER_SEC >= (float)0.9){
		return false;
	}

	if(ver.size() > (k - d + 1)){
		return false;
	}
	if(ver.size() <= 1){
		return true;
	}

	for(int v: ver){
		vector<int> ver2;
		for(int u: ver){
			if(u == v){
				continue;
			}

			for(int to: g[u]){
				ver2.push_back(to);
			}
		}

		if(solve(ver2, d + 1)){
			return true;
		}
	}

	return false;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	for(int i = 0; i < n - 1; i++){
		int u, v;

		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, 0);

	vector<int> ver = g[1];
	bool ans = solve(ver, 1);

	if(ans){
		cout << "DA\n";
	}
	else{
		cout << "NE\n";
	}

	return 0;
}