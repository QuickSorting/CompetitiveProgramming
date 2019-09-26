/*
	Used the tutorial
*/

#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 407;
const int MAX_M = 60007;
const int MAX_A = 27;
const int MAX_NODES = MAX_N * MAX_N * MAX_A;

int n, m;

inline int to_idx(int u, int v, int c){
	return (u - 1) * MAX_N * MAX_A + (v - 1) * MAX_A + c;
}

pair<int, int> from_idx(int idx){
	pair<int, int> ret;

	ret.first = idx / MAX_N / MAX_A;
	ret.second = (idx / MAX_A) % MAX_N;

	++ret.first;
	++ret.second;

	return ret;
}

inline int idx_char(int idx){
	return idx % MAX_A;
}

int a[MAX_N];
vector<pair<int, int> > adj1[MAX_N], adj2[MAX_N];
vector<int> en0, en1;
bool used[MAX_NODES];
int par[MAX_NODES];

map<pair<int, int>, int> mp;
queue<int> q;

int main(){
	scanf("%d %d", &n, &m);

	for(int i = 0; i < m; ++i){
		int u, v;
		char c;

		scanf("%d %d %c", &u, &v, &c);
		c -= 'a';

		en1.push_back(to_idx(u, v, 26));
		mp[{u, v}] = c;

		adj1[v].push_back({u, c});
		adj2[u].push_back({v, c});
	}

	for(int u = 1; u <= n; ++u){
		en0.push_back(to_idx(u, u, 26));
	}

	for(int i = 1; i < MAX_NODES; ++i){
		par[i] = -2;
	}
	for(int x: en0){
		q.push(x);
		used[x] = true;
		par[x] = -1;
	}

	while(!q.empty()){
		int x = q.front();
		q.pop();

		if(x == en0.back()){
			for(int y: en1){
				q.push(y);
				used[y] = true;
				par[y] = -1;
			}
		}

		pair<int, int> pos = from_idx(x);
		int curr_ch = idx_char(x);

		if(curr_ch == 26){
			for(pair<int, int> to: adj1[pos.first]){
				int tidx = to_idx(to.first, pos.second, to.second);
				if(used[tidx]){
					continue;
				}

				par[tidx] = x;
				used[tidx] = true;
				q.push(tidx); 
			}
		}
		else{
			for(pair<int, int> to: adj2[pos.second]){
				int tidx = to_idx(pos.first, to.first, 26);
				if(to.second != curr_ch || used[tidx]){
					continue;
				}

				par[tidx] = x;
				used[tidx] = true;
				q.push(tidx); 
			}
		}
	}

	int d;

	cin >> d;

	for(int i = 0; i < d; ++i){
		cin >> a[i];
	}

	for(int i = 1; i < d; ++i){
		string s1 = "";
		string s2 = "";

		int curr = to_idx(a[i - 1], a[i], 26);
		if(par[curr] == -2){
			printf("-1\n");
			//cout << "-1\n";
			continue;
		}

		while(par[curr] != -1){
			if(idx_char(curr) == 26){
				s1 += (char)(idx_char(par[curr]) + 'a');
			}
			else{
				s2 += (char)(idx_char(curr) + 'a');
			}
			curr = par[curr];
		}

		string ans = s1;
		pair<int, int> pos = from_idx(curr);
		if(pos.first != pos.second){
			ans += (char)('a' + mp[pos]);
		}
		reverse(s2.begin(), s2.end());
		ans += s2;

		//cout << ans.size() << " " << ans << "\n";
		printf("%d ", (int)ans.size());
		for(char c: ans){
			printf("%c", c);
		}
		printf("\n");
	}

	return 0;
}