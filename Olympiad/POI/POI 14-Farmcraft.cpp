/*
	-A subtree should be explored before another if (max1 + time2) > (max2 + time1)
	-So we can sort by (max1 - time1) and then solve recursively
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 7;

int a[MAXN], cnt[MAXN];
vector<int> adj[MAXN];
int n;

void dfs(int u, int par){
	cnt[u] = 1;

	for(int to: adj[u]){
		if(to == par)
			continue;

		dfs(to, u);
		cnt[u] += cnt[to];
	}
}

int solve(int u, int par){
	int ret = 0;
	if(par != -1)
		ret = max(ret, a[u]);
	else
		ret = max(ret, a[u] + 2 * (cnt[u] - 1));

	vector<array<int, 4> > order;
	for(int to: adj[u]){
		if(to == par)
			continue;

		int curr = solve(to, u);
		order.push_back({curr - 2 * cnt[to], curr, cnt[to], to});
	}

	sort(order.begin(), order.end());
	reverse(order.begin(), order.end());

	int time = 0;
	for(auto p: order){
		++time;
		ret = max(ret, p[1] + time);
		time += 2 * (p[2] - 1);
		++time;
	}

	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
	}

	for(int i = 1; i <= n - 1; ++i){
		int u, v;
		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, -1);

	cout << solve(1, -1) << "\n";
}