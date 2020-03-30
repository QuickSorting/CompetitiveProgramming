/*
	Followed tutorial
*/
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const int k_N = 2e4 + 1;
const int k_M = 3e4 + 1;
const int k_Q = 2e4 + 1;
const int k_K = 15 + 1;
const int k_P = 30 + 1;

int n, k, m, p, q;
string s[k_N][k_K], t[k_M];
int indices[k_K];

unordered_map<string, int> cnt;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("sabin.in", "r", stdin);
	freopen("sabin.out", "w", stdout);
	
	cin >> n >> k >> m >> p >> q;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < k; ++j)
			cin >> s[i][j];

	for(int i = 0; i < n; ++i){
		string str = "";
		for(int pr = 0; pr < p; ++pr){
			for(int j = 0; j < k; ++j)
				str += s[i][j][pr];
			++cnt[str]; 
		}
	}

	for(int i = 0; i < m; ++i)
		cin >> t[i];

	while(q--){
		int x;

		cin >> x;
		for(int i = 0; i < k; ++i){
			cin >> indices[i];
			--indices[i];
		}

		if(x > p){
			cout << "0\n";
			continue;
		}

		string str = "";
		int ans = 0;
		for(int j = 0; j < x; ++j)
			for(int i = 0; i < k; ++i)
				str += t[indices[i]][j];
		
		if(x)
			ans += cnt[str];
		else
			ans += n;

		if(x < p){
			str = "";
			for(int j = 0; j < x + 1; ++j)
				for(int i = 0; i < k; ++i)
					str += t[indices[i]][j];

			ans -= cnt[str];
		}

		cout << ans << "\n";
	}
}