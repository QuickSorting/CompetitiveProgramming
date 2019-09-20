#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 32;
const long long MAXI = 600;
const long long mod = 1234567;

long long dp[MAXI][MAXI][MAXN], dp2[MAXN][MAXN][MAXI];
long long sum[MAXI];

inline int max_inv(int n){
	return n * n;
}

inline int get_dp2(int n1, int n2, int i){
	if(i < 0 || n1 < 0 || n2 < 0){
		return 0;
	}
	
	return dp2[n1][n2][i];
}

inline int get_dp(int i1, int i2, int n){
	if(i1 < 0 || i2 < 0 || n < 0 || i1 > max_inv(n) || i2 > max_inv(n)){
		return 0;
	}

	return dp[i1][i2][n];
}

void precompute(int maxn){
	for(int n1 = 0; n1 <= maxn; ++n1){
		for(int n2 = 0; n2 <= maxn; ++n2){
			for(int i = 0; i <= max_inv(maxn); ++i){
				if(n1 + n2 + i == 0){
					dp2[n1][n2][i] = 0;
					continue;
				}
				dp2[n1][n2][i] = get_dp2(n1 - 1, n2, i - n2) + get_dp2(n1, n2 - 1, i);
				dp2[n1][n2][i] %= mod;
			} 
		}
	}

	for(int i1 = 0; i1 <= max_inv(maxn); ++i1){
		for(int i2 = 0; i2 <= max_inv(maxn); ++i2){
			for(int n = 0; n <= maxn; ++n){
				if(i1 + i2 + n == 0){
					dp[i1][i2][n] = 0;
					continue;
				}

				for(int x = 1; x <= n; ++x){
					for(int q = 0; q <= i1 - (n - 1); ++q){
						for(int s = 0; s <= max_inv(n); ++s){
							sum[s] = 0;
						}

						for(int l = 0; l <= max_inv(n); ++l){
							for(int r = 0; r <= max_inv(n) - l; ++r){
								sum[l + r] += get_dp(x - 1, q, l) * get_dp(n - x,  i1 - (n - 1) - q, r) % mod;
								sum[l + r] %= mod;
							}
						}


					}
				}
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, x;

	cin >> n >> x;

	int mx2 = n * (n - 1) / 2;
	int mx1 = (n + 2) * (n - 1) / 2;

	for(int i = 0; i <= mx2; ++i){
		for(int j = 0; j <= i * x; ++j){

		}
	}
}