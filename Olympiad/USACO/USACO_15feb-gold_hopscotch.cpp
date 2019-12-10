/*
	-Followed the tutorial
*/
#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9 + 7;
const int MAXN = 757;

struct fenwick{
	vector<long long> arr;
	int sz;

	fenwick(int sz = 0){
		this->sz = sz + 2;
		arr.resize(this->sz, 0);
	}

	void update(int idx, long long val){
		for(++idx; idx < sz; idx += (idx & -idx)){
			arr[idx] += val;
			arr[idx] %= mod;
		}
	}

	long long query(int idx){
		long long ret = 0;
		for(++idx; idx >= 1; idx -= (idx & -idx)){
			ret += arr[idx];
			ret %= mod;
		}
		return ret;
	}

	long long query_rev(int l){
		return (query(sz - 2) - query(l) + mod) % mod;
	}
};

int r, c, k, a[MAXN][MAXN];
set<int> is[MAXN * MAXN];
vector<int> appearence[MAXN * MAXN];

long long sum[MAXN * MAXN];
fenwick sum_specific[MAXN * MAXN];

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
		sort(appearence[i].begin(), appearence[i].end());
	}

	for(int i = 1; i <= k; ++i)
		sum_specific[i] = fenwick((int)appearence[i].size());

	sum[c - 1] = 1;
	{
		int val = a[r - 1][c - 1];
		sum_specific[val].update(appearence[val].size() - 1, 1);
	}

	for(int i = r - 2; i >= 0; --i){
		long long curr = 0;
		for(int k = 0; k < c; ++k){
			curr += sum[k];
			curr %= mod;
		}

		for(int j = 0; j < c; ++j){
			curr -= sum[j];
			curr += mod;
			curr %= mod;

			int l = 0, r = (int)appearence[a[i][j]].size() - 1;
			while(l != r){
				int mid = (l + r) >> 1;

				if(appearence[a[i][j]][mid] < j)
					l = mid + 1;
				else
					r = mid;
			}

			int idx = l;
			long long add = curr - sum_specific[a[i][j]].query_rev(idx);
			add += mod;
			add %= mod;

			if(i == 0 && j == 0){
				cout << add << "\n";
				return;
			}

			sum[j] += add;
			sum[j] %= mod;
			sum_specific[a[i][j]].update(idx, add);
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