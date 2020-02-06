#include "aliens.h"
#include <bits/stdc++.h>

const long long kMaxVal= 1e18;

int n, m, k;
std::vector<int> r, c;
std::vector<std::pair<int, int> > p;
std::vector<std::vector<long long> > dp;

inline long long square(const long long &x){
	return x * x;
}

long long solve(){
	for(int j = 0; j < n; ++j){
		dp[k][j] = kMaxVal;
	}
	dp[k][n] = 0;

	for(int i = k - 1; i >= 0; --i){
		for(int j = 0; j < n; ++j){
			dp[i][j] = kMaxVal;
			int max = p[j].second;

			for(int to = j; to < n; ++to){
				max = std::max(max, p[to].second);

				long long curr = square(max - p[j].first + 1) + dp[i + 1][to + 1];
				if(to + 1 != n)
					curr -= square(std::min(max, p[to + 1].second) - p[to + 1].first + 1);

				dp[i][j] = std::min(dp[i][j], curr);
			}
		}
		dp[i][n] = 0;
	}

	return dp[0][0];
}

void initialize(){
	p.resize(n);
	dp.resize(k + 1, std::vector<long long>(n + 1));

	for(int i = 0; i < n; ++i){
		if(r[i] > c[i])
			std::swap(r[i], c[i]);
		p[i] = {r[i], c[i]};
	}
	sort(p.begin(), p.end());
}

long long take_photos(int _n, int _m, int _k, std::vector<int> _r, std::vector<int> _c){
	n = _n, m = _m, k = _k;
	r = _r, c = _c;

	initialize();
	return solve();
}
