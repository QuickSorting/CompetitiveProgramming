#include "aliens.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 7;
const long long inf = 1e18;
const long long inf_two = 1e12;

pair<int, int> p[MAXN];
pair<long long, int> dp[MAXN];

void sort_array(int &n, vector<int> &r, vector<int> &c){
	for(int i = 0; i < n; ++i){
		if(r[i] > c[i])
			swap(r[i], c[i]);

		p[i] = {r[i], c[i]};
	}
	sort(p, p + n);
}

void remove_unnecessary(int &n){
	vector<pair<int, int> > tmp;
	int i = 0;
	while(i < n){
		tmp.push_back(p[i]);

		int j = i + 1;
		while(j < n && p[i].second >= p[j].second)
			++j;
		i = j;
	}

	n = (int)tmp.size();
	for(int i = 0; i < n; ++i)
		p[i] = tmp[i];
}

void init_array(int &n, vector<int> &r, vector<int> &c){
	sort_array(n, r, c);
	remove_unnecessary(n);
}

pair<long long, int> do_dp(const int &n, const long long &price){
	dp[n] = {0, 0};
	for(int pos = n - 1; pos >= 0; --pos){
		dp[pos] = {inf, 0};

		long long mx = 0; 
		for(int next_pos = pos; next_pos < n; ++next_pos){
			mx = max(mx, (long long)p[next_pos].second - p[pos].first + 1); 

			pair<long long, int> curr = {mx * mx + dp[next_pos + 1].first + price, 
				                         dp[next_pos + 1].second + 1};

			if(next_pos + 1 != n && p[next_pos + 1].first <= p[pos].first + mx - 1){
				long long diff = p[pos].first + mx - p[next_pos + 1].first;
				curr.first -= diff * diff;
			}

			dp[pos] = min(dp[pos], curr);
		}
	}

	return dp[0];
}

long long div2(long long x){
	if((x & 1) && (x < 0))
		return (x / 2) - 1;
	return (x / 2);
}

long long solve(const int &n, const int &k){
	long long l = 0, r = inf_two;
	while(l != r){
		long long mid = (l + r) / 2;
		if(do_dp(n, mid).second <= k)
			r = mid;
		else
			l = mid + 1; 
	}

	pair<long long, int> ans = do_dp(n, l);
	return ans.first - l * ans.second;
}

long long take_photos(int n, int m, int k, vector<int> r, vector<int> c){
	init_array(n, r, c);
  	return solve(n, k);
}
