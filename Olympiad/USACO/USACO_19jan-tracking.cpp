/*
	-We first find the maxiumum minimum at each position using multiset.
	-By doing this, we actually find the minimum value that can be at this position.
	-We also notice that if we have two adjacent positions i and i + 1, then if one
	 of them is smaller than the other one, that means that the value at this position is
	 the same as the minimum. For example if the minimums we get are:
	 			a = [1, 1, 2, 2]
	 			     0  1  2  3
	-Then that means that the minimum went from 1 to 2 at positions 1 and 2, and that happens
	 only if the value at position 1 is the minimum - 1.
	-So if we have k = 2, then we also have min(x[1], x[2]) = 1 and min(x[2], x[3]) = 2, so x[1] is obviously 1.
	-Then we can do dynamic programming for every interval with the same values.
	-For example:
				a = [1, 1, 2, 2, 1, 3]
	-Then we do dp on [1, 1], [2, 2], [1], [3] independantly
	-The state of the dp is the position, at which we are, and the value is the number of ways to choose values
	 in such a way that there is a minimum value in every k consecutive positions.
	-The idea is to assume we are not choosing any minimum, then for each x[i] we have (inf - x[i]) ways to choose it
	-Then we can decide which of the next k position holds the minimum.
	-Because the interval remains with the same size - k, we can just maintian the sum of 
	 {the number of ways we get if we choose this specific position to be the first next minimum}
	-Because we use multiset and fast powers, the solutions has a complexity of O(nlogn)
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 7;
const long long mod = 1e9 + 7;
const long long inf = 1e9;

int n, k;
long long c[MAXN], a[MAXN], dp[MAXN];

long long fast_pow(long long base, int exp){
	if(!exp)
		return 1ll;

	if(exp & 1)
		return (fast_pow(base, exp - 1) * base) % mod;
	long long half = fast_pow(base, exp / 2);
	return (half * half) % mod;
}

long long mod_inverse(long long x){
	return fast_pow(x, mod - 2ll);
}

long long solve(int pos, int rend, bool start){
	if(pos >= rend)
		return 1;

	long long sum = mod_inverse(inf - a[rend - 1]);
	dp[rend] = sum;
	for(int i = rend - 1; i >= pos; --i){
		if(i + k < rend){
			sum -= dp[i + k + 1];
			sum += mod;
			sum %= mod;
		}
		dp[i] += sum;
		dp[i] %= mod;
		if(i + k > rend && (!start || i != pos))
			dp[i] += 1;
		dp[i] %= mod;

		if(i == pos)
			return dp[i];
		dp[i] *= mod_inverse(inf - a[i - 1]);
		dp[i] %= mod;
		sum += dp[i];
		sum %= mod;
	}

	return -1;
}

void solve(){
	multiset<int> mx;
	for(int i = 0; i < n; ++i){
		if(i <= n - k)
			mx.insert(c[i]);
		if(i >= k)
			mx.erase(mx.find(c[i - k]));
		a[i] = *mx.rbegin();
	}


	int start = 0;
	long long ans = 1;
	for(int i = 0; i < n; ++i){
		if(i == n - 1 || a[i] != a[i + 1]){
			if(a[i] == inf){
				start = i + 1;
				continue;
			}

			int l = start, r = i + 1;
			bool changed = false;
			if(l != 0 && a[l - 1] > a[l]){
				++l;
				changed = true;
			}
			if(r != n && a[r - 1] < a[r]){
				--r;
				changed = true;
			}

			for(int j = l; j < r; ++j){
				ans *= (inf - a[j]);
				ans %= mod;
			}

			ans *= solve(l, r, !changed);
			ans %= mod;
			start = i + 1;
		}
	}


	cout << ans << "\n";
}

void read(){
	freopen("tracking2.in", "r", stdin);
	freopen("tracking2.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	for(int i = 0; i <= n - k; ++i){
		cin >> c[i];
	}
}

int main(){
	read();
	solve();
}