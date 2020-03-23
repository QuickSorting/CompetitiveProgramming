/*
	-Followed the tutorial
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 5007;
const int kMod = 1e9 + 7;

int n, k;
long long dp[kN][kN], partitions[kN][kN], sum[kN][kN];

long long get_sum(int l, int r, int parts){
	if(l == 0)
		return sum[parts][r];
	return (sum[parts][r] - sum[parts][l - 1] + kMod) % kMod;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;

	dp[1][0] = 1;
	for(int cnt = 1; cnt <= n; ++cnt){
		for(int pairs = 0; pairs < cnt; ++pairs){
			dp[cnt + 1][pairs + 1] += dp[cnt][pairs];
			dp[cnt + 1][pairs + 1] %= kMod;

			if(pairs){
				dp[cnt + 1][pairs - 1] += dp[cnt][pairs] * pairs;
				dp[cnt + 1][pairs - 1] %= kMod;
			}

			dp[cnt + 1][pairs] += dp[cnt][pairs] * (cnt - pairs);
			dp[cnt + 1][pairs] %= kMod;
		}
	}

	partitions[0][0] = 1;
	for(int cnt = 0; cnt <= n; ++cnt)
		sum[0][cnt] = 1;

	for(int parts = 1; parts <= n; ++parts){
		for(int cnt = parts; cnt <= n; ++cnt){
			partitions[parts][cnt] = get_sum(max(cnt - k, 0), cnt - 1, parts - 1);
			sum[parts][cnt] = sum[parts][cnt - 1] + partitions[parts][cnt];
			sum[parts][cnt] %= kMod;
		}
	}

	long long ans = 0;
	for(int parts = 1; parts <= n; ++parts){
		ans += partitions[parts][n] * dp[parts][0];
		ans %= kMod;
	}

	cout << ans << "\n";
}
