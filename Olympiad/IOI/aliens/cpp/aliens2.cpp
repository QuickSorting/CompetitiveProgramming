#include "aliens.h"
#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 4007;
const long long inf = 1e18;
 
pair<int, int> p[MAXN];
long long dp[MAXN][MAXN];
 
void init_array(int &n, const int &m, vector<int> &r, vector<int> &c){
	for(int i = 0; i < n; ++i){
		if(r[i] > c[i])
			swap(r[i], c[i]);
 
		p[i] = {r[i], c[i]};
	}
	sort(p, p + n);
 
	vector<pair<int, int> > tmp;
	int i = 0;
	while(i < n){
		tmp.push_back(p[i]);
 
		int j = i + 1;
		while(j < n && p[i].second >= p[j].second){
			++j;
		}
		i = j;
	}
 
	n = (int)tmp.size();
	for(int i = 0; i < n; ++i)
		p[i] = tmp[i];
}
 
long long do_dp(const int &n, const int &m, const int &k){
	for(int pos = 0; pos < n; ++pos)
		dp[0][pos] = inf;
	dp[0][n] = 0;
 
	for(int groups = 1; groups <= k; ++groups){
		for(int pos = 0; pos < n; ++pos){
			dp[groups][pos] = inf;
 
			long long mx = 0; 
			for(int next_pos = pos; next_pos < n; ++next_pos){
				mx = max(mx, (long long)p[next_pos].second  - p[pos].first + 1); 
 
				long long curr = mx * mx + dp[groups - 1][next_pos + 1];
				if(next_pos + 1 != n && p[next_pos + 1].first <= p[pos].first + mx - 1){
					long long diff = p[pos].first + mx - p[next_pos + 1].first;
					curr -= diff * diff;
				}
 
				dp[groups][pos] = min(dp[groups][pos], curr);
			}
		}
		dp[groups][n] = 0;
	}
 
	return dp[k][0];
}
 
long long take_photos(int n, int m, int k, vector<int> r, vector<int> c){
	init_array(n, m, r, c);
  	return do_dp(n, m, k);
}