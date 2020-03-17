/*
	-Followed tutorial
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 101;
const int kD = 51;

int n, m;
long long z;
bool adj[kN][kN];
long long ways[kN][kN][kD], good[kN][kN][kD];
int ans[kN][kN][kD];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> z;
	for(int i = 0; i < m; ++i){
		int u, v;
		cin >> u >> v;

		adj[u][v] = 1; 
	}

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			ways[i][j][0] = (i == j);

	for(int dist = 1; dist < kD; ++dist){
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				ways[i][j][dist] = 0;
				for(int k = 1; k <= n; ++k){
					if(adj[i][k]){
						ways[i][j][dist] += ways[k][j][dist - 1];
						if(ways[i][j][dist] >= z)
							ways[i][j][dist] -= z;
					}
				}
			}
		}
	}

	for(int u = 1; u <= n; ++u){
		for(int v = u; v <= n; ++v){
			array<int, 2> ends{u, v};
			for(int j = 1; j < kD; ++j){
				for(int a: ends){
					for(int b: ends){
						good[a][b][j] = ways[a][b][j];
						for(int last: ends){
							for(int when = 1; when <= j - 1; ++when){
								good[a][b][j] -= good[a][last][when] * ways[last][b][j - when];
								good[a][b][j] %= z;
								if(good[a][b][j] < 0)
									good[a][b][j] += z;
							}
						}
					}
				}
				ans[u][v][j] = good[u][v][j];
				ans[v][u][j] = good[v][u][j];
			}
		}
	}

	int q;
	cin >> q;
	for(int i = 0; i < q; ++i){
		int u, v, d;
		cin >> u >> v >> d;

		cout << ans[u][v][d] << "\n";
	}
}