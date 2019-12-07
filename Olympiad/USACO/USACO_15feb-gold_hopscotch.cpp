#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9 + 7;
const int MAXN = 757;

struct fenwick{
	long long arr[MAXN];
	fenwick(){}

	void update(int idx, long long val){
		for(++idx; idx < MAXN; idx += (idx & -idx)){
			arr[idx] += val;
		}
	}

	long long query(int idx, long long val){
		long long ret = 0;
		for(++idx; idx >= 1; idx -= (idx)){
			ret += arr[idx];
		}
		return ret;
	}
};

int r, c, k;
int a[MAXN][MAXN];
set<int> is[MAXN * MAXN];
vector<int> appearence[MAXN * MAXN];
long long sum[MAXN];

void solve(){
	for(int i = 0; i < r; ++i){
		for(int j = 0; j < c; ++j){
			is[a[i][j]].insert(j);
		}
	}

	for(int i = 1; i <= k; ++i){
		for(int x: is[i]){
			appearence[i].push_back(x);
		}
	}

	sum[c - 1] = 1;
	sum_specific[c - 1][a[r - 1][c - 1]] = 1;

	for(int i = r - 2; i >= 0; --i){
		for(int j = 0; j < c; ++j){
			long long curr = 0;
			for(int k = j + 1; k < c; ++k){
				curr += sum[k] - sum_specific[k][a[i][j]];
				curr += mod;
				curr %= mod;
			}

			if(i == 0 && j == 0){
				cout << curr << "\n";
				return;
			}

			sum[j] += curr;
			sum[j] %= mod;
			sum_specific[j][a[i][j]] += curr;
			sum_specific[j][a[i][j]] %= mod;
		}
	}
}	

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("hopscotch.in", "r", stdin);
	freopen("hopscotch.out", "w", stdout);

	cin >> r >> c >> k;
	for(int i = 0; i < r; ++i){
		for(int j = 0; j < c; ++j){
			cin >> a[i][j];
		}
	}
}

int main(){
	read();
	solve();
}