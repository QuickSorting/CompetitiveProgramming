/*
	Followed the tutorial - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2002
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 207;

struct max_flow{
	vector<int> adj[4 * MAXN * MAXN];
	array<int, 3> edge[4 * MAXN * MAXN];
	int parent[4 * MAXN * MAXN], idx, s, t;
	const int inf = 1e9;

	max_flow(){
		idx = 0;
		s = t = 0; 
	}

	void add_edge(int x, int y, int val){
		adj[x].push_back(idx);
		adj[y].push_back(idx + 1);
		edge[idx] = {x, y, val};
		edge[idx + 1] = {y, x, 0};
		idx += 2;
		t = max(t, max(x, y));

		//cout << "edge " << x << " " << y << " " << val << "\n";
	}

	int dfs(){
		for(int i = 0; i <= t; ++i){
			parent[i] = -1;
		}

		stack<array<int, 2> > st;

		st.push({s, inf});
		parent[s] = -2;

		while(!st.empty()){
			array<int, 2> arr = st.top();
			st.pop();

			int u = arr[0];
			int val = arr[1];

			if(u == t){
				return val;
			}

			for(int i: adj[u]){
				int to = edge[i][1];

				if(edge[i][2] <= 0 || parent[to] != -1){
					continue;
				}

				parent[to] = i;
				st.push({to, min(val, edge[i][2])});
			}
		}

		return 0;
	}

	int calc_max_flow(){
		int flow = 0, new_flow;

		while(new_flow = dfs()){
			flow += new_flow;
			//cout << new_flow << " new_flow\n";

			int curr = t;
			while(curr != s){
				//cout << curr << " ";
				int i = parent[curr];
				edge[i][2] -= new_flow;
				edge[i ^ 1][2] += new_flow;
				curr = edge[i][0];
			}
			//cout << s << "\n";
		}

		return flow;
	}
};

int n, m;
short a[MAXN][MAXN];
bool used[MAXN][MAXN];
int col[MAXN][MAXN], row[MAXN][MAXN];
int w_col[MAXN * MAXN], w_row[MAXN * MAXN];
max_flow mf;

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			cin >> a[i][j];
		}
	}
}

void solve(){
	int cnt_r = 0, cnt_c = 0;

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			row[i][j] = -1;
			col[i][j] = -1; 
		}
	}

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(row[i][j] == -1 && a[i][j] != 2){
				for(int k = i; k >= 0; --k){
					if(a[k][j] == 2){
						break;
					}
					else{
						row[k][j] = cnt_r;
					}
				}
				for(int k = i + 1; k < n; ++k){
					if(a[k][j] == 2){
						break;
					}
					else{
						row[k][j] = cnt_r;
					}
				}
				w_row[cnt_r] = j;
				++cnt_r;
			}

			if(col[i][j] == -1 && a[i][j] != 2){
				for(int k = j; k >= 0; --k){
					if(a[i][k] == 2){
						break;
					}
					else{
						col[i][k] = cnt_c;
					}
				}
				for(int k = j + 1; k < m; ++k){
					if(a[i][k] == 2){
						break;
					}
					else{
						col[i][k] = cnt_c;
					}
				}
				w_col[cnt_c] = i;
				++cnt_c;
			}
		}
	}

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(a[i][j] == 0){
				mf.add_edge(row[i][j] + 1, col[i][j] + cnt_r + 1, 1);
			}
		}
	}

	for(int i = 0; i < cnt_r; ++i){
		mf.add_edge(0, i + 1, 1);
	}
	for(int i = 0; i < cnt_c; ++i){
		mf.add_edge(i + cnt_r + 1, cnt_c + cnt_r + 1, 1);
	}

	int ans = mf.calc_max_flow();
	cout << ans << "\n";

	for(int i = 0; i < mf.idx; ++i){
		array<int, 3> e = mf.edge[i];

		if(e[0] != 0 && e[1] != mf.t && e[1] != 0 && e[1] != mf.t){
			if(e[0] < e[1] && e[2] == 0){
				cout << w_col[e[1] - cnt_r - 1] + 1 << " " << w_row[e[0] - 1] + 1 << "\n";
				--ans;
			}
		} 
	}

	while(ans != 0);

	return;
}

int main(){
	read();
	solve();
}
/*
3 4
2 0 1 1
2 2 2 1
0 1 0 2
*/