/*
	-We make a dp[pr][pos] where pr is the beginning of the previous line and pos
	is the beginning of the current one
	-dp[pr][pos] is equal to the minimum coefficent of aesthism if we only had the
	words >= pr and the first line began with pr and the second one with pos
	-Then for each pos we calculate all dp[j][pos] by first finding m_idx which is the
	first index where the line containing pos,...,m_idx is too big, and for each j finding 
	the first index where the line containg pos,...,plus_idx is larger than pr,...,pos - 1
	-That way if the other end of the next line is from pos to plus_idx - 1 then we know that
	abs(line[nxt] - line[curr]) = line[curr] - line[nxt], and if it is from plus_idx to m_idx - 1 then
	abs(line[nxt] - line[curr]) = line[nxt] - line[curr]. By doing this, we can easily find the minimum
	by using prefix and suffix arrays for the value dp[pos][nxt] + abs(line[nxt] - line[curr]).
*/
#include <bits/stdc++.h>

using namespace std;

const long long kN = 2e3 + 7;
const long long kM = 1e6 + 7;
const long long inf = 1e18;

long long a[kN], prefix[kN];
long long dp[kN][kN];
long long plus_st[kN], minus_st[kN];

long long get_sum(long long l, long long r){
	long long ret = prefix[r] + r - l;
	if(l)
		ret -= prefix[l - 1];
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long m, n;
	cin >> m >> n;

	for(int i = 0; i < n; ++i)
		cin >> a[i];

	prefix[0] = a[0];
	for(int i = 1; i < n; ++i)
		prefix[i] = a[i] + prefix[i - 1];

	for(int i = 0; i < n; ++i){
		if(get_sum(i, n - 1) <= m)
			dp[i][n] = 0;
		else
			dp[i][n] = inf;
	}

	for(int i = n - 1; i >= 0; --i){
		for(int nxt = i + 1; nxt <= n; ++ nxt){
			plus_st[nxt] =  dp[i][nxt] + get_sum(i, nxt - 1);
			minus_st[nxt] =  dp[i][nxt] - get_sum(i, nxt - 1);
		}

		int l = i, r = n;
		while(l != r){
			int mid = (l + r) >> 1;
			if(get_sum(i, mid) > m)
				r = mid;
			else
				l = mid + 1;
		}
		int m_idx = l;
		int plus_idx = i;

		plus_st[m_idx + 1] = inf;
		//plus_st[m_idx] = plus_st[m_idx];
		for(int nxt = m_idx - 1; nxt >= i + 1; --nxt)
			plus_st[nxt] = min(plus_st[nxt + 1], plus_st[nxt]);
		
		minus_st[i] = inf;
		//minus_st[i + 1] = minus_st[i + 1];
		for(int nxt = i + 2; nxt <= m_idx; ++nxt)
			minus_st[nxt] = min(minus_st[nxt - 1], minus_st[nxt]);

		for(int j = i - 1; j >= 0; --j){
			long long curr = get_sum(j, i - 1);
			if(curr > m){
				dp[j][i] = inf;
				continue;
			}

			while(plus_idx < n && get_sum(i, plus_idx) < curr)
				++plus_idx;

			dp[j][i] = min(plus_st[plus_idx + 1] - curr, minus_st[plus_idx] + curr);
		}
	}

	long long ans = inf;
	for(int i = 1; i <= n; ++i)
		ans = min(ans, dp[0][i]);

	cout << ans << "\n";	
}