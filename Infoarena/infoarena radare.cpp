#include <bits/stdc++.h>

using namespace std;

const int kMod = 31333;
const int kN = 3007;
const int kP = 3507;
void read();

int n, p, val[kN], cnt_subtree[kN];
vector<int> adj[kN];
int order[kN], end_idx[kN], timer;
int dp[kN][kP], pow2[kN];

void dfs(int u, int parent = -1){
	order[timer++] = u;
	for(int to: adj[u]){
		if(to == parent)
			continue;

		dfs(to, u);
		cnt_subtree[u] += cnt_subtree[to] + 1;
	}
	end_idx[u] = timer - 1;
}

inline void fix_mod(int &x){
	x = (x >= kMod) ? (x - kMod) : x;
}

void preprocess_pow2(){
	pow2[0] = 1;
	for(int i = 1; i <= n; ++i){
		pow2[i] = pow2[i - 1] << 1;
		fix_mod(pow2[i]);
	}
}

inline int get_dp(int pos, int curr){
	return ((curr > p) ? 0 : dp[pos][curr]);
}

void calc_dp(){
	dp[n - 1][p] = 1;
	for(int pos = n - 2; pos >= 0; --pos){
		for(int curr = 0; curr <= p; ++curr){
			dp[pos][curr] = get_dp(pos + 1, curr + val[order[pos + 1]]);

			dp[pos][curr] += get_dp(end_idx[order[pos + 1]], curr) * pow2[cnt_subtree[order[pos + 1]]] % kMod;
			fix_mod(dp[pos][curr]);
		}
	}
}

int main(){
	read();
	dfs(1);
	preprocess_pow2();
	calc_dp();

	printf("%d\n", dp[0][val[1]]);
}

void read(){
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	freopen("radare.in", "r", stdin);
	freopen("radare.out", "w", stdout);

	scanf("%d %d", &n, &p);

	for(int i = 0; i < n - 1; ++i){
		int u, v;
		scanf("%d %d", &u, &v);

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 1; i <= n; ++i)
		scanf("%d", &val[i]);
}