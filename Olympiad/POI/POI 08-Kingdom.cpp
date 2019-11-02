#include <bits/stdc++.h>

using namespace std;

const int MAXN = 32;

int n, m, ans = 0;
bool adj[MAXN][MAXN];

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		int u, v;

		cin >> u >> v;
		--u;
		--v;
		adj[u][v] = true;
		adj[v][u] = true;
	}
}

void solve(){
	int ans_edge = m + 1;
	for(int i = 0; i < (1 << (n - 1)); ++i){
		int cnt = 0;
		for(int j = 0; j < n; ++j){
			cnt += (bool)(i & (1 << j));
		}

		if(cnt != n / 2){
			continue;
		}

		int curr_edge = 0;
		for(int j = 0; j < n; ++j){
			if(i & (1 << j)){
				for(int k = 0; k < n; ++k){
					if(!(i & (1 << k))){
						curr_edge += adj[j][k];
					}
				}
			}
		}

		//cout << curr_edge << " curr_edge\n"; 

		if(curr_edge < ans_edge){
			ans_edge = curr_edge;
			ans = i;
		}
	}
}

void write(){
	for(int i = 0; i < n; ++i){
		bool one = !(ans & 1);
		bool two = ans & (1 << i);
		if(one ^ two){
			cout << i + 1 << " ";
		}
	}
	cout << "\n";
}

int main(){
	read();
	solve();
	write();
}