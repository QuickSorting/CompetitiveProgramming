/*
	-Followed tutorial
*/
#include <bits/stdc++.h>

using namespace std;

const int kMod = 30011;
const int kN = 251;

int fpow(int base, int exp){
	if(!exp)
		return 1;
	if(exp & 1)
		return base * fpow(base, exp ^ 1) % kMod;

	int t = fpow(base, exp >> 1);
	return t * t % kMod;
}

int n, k;
int cnt_trees[kN], cnt_cycles[kN], combination[kN][kN];
int cnt_fill[kN][kN], dp[kN], dp2[kN];

void init_cnt_trees(){
	cnt_trees[0] = cnt_trees[1] = cnt_trees[2] = 1;
	for(int i = 3; i <= n; ++i)
		cnt_trees[i] = fpow(i, i - 2);
}

void init_combination(){
	combination[0][0] = 1;
	for(int i = 1; i <= n; ++i){
		combination[i][0] = combination[i][i] = 1;
		for(int j = 1; j < i; ++j)
			combination[i][j] = (combination[i - 1][j] + combination[i - 1][j - 1]) % kMod;
	}
}

void init_cnt_cycles(){
	cnt_cycles[3] = 1;
	for(int i = 4; i <= n; ++i)
		cnt_cycles[i] = (i - 1) * cnt_cycles[i - 1] % kMod;
}

int fill_in_tree(int num_remain, int len_cycle) {
	if(!len_cycle)
		return !num_remain;

	if(cnt_fill[num_remain][len_cycle] != -1)
		return cnt_fill[num_remain][len_cycle];

	int &ans = cnt_fill[num_remain][len_cycle] = 0;
	for(int i = 0; i <= num_remain; ++i){
		ans += combination[num_remain][i] * cnt_trees[i + 1] % kMod * fill_in_tree(num_remain - i, len_cycle - 1) % kMod;
		ans %= kMod;
	}

	return ans;
}

int solve(int x){
	if(x < k)
		return 0;

	int ans = 0;
	for(int cycle = k; cycle <= x; ++cycle){
		ans += fill_in_tree(x - cycle, cycle) * cnt_cycles[cycle] % kMod * combination[x][cycle] % kMod;
		ans %= kMod;
	}

	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("shgraf.in", "r", stdin);
	freopen("shgraf.out", "w", stdout);

	cin >> n >> k;

	init_combination();
	init_cnt_cycles();
	init_cnt_trees();

	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			cnt_fill[i][j] = -1;

	for(int i = 1; i <= n; ++i)
		dp2[i] = solve(i);

	dp[0] = 1;
	for(int i = k; i <= n; ++i){
		dp[i] = 0;
		for(int j = 1; j <= i; ++j){
			dp[i] += dp[i - j] * dp2[j] % kMod * combination[i - 1][j - 1] % kMod;
			dp[i] %= kMod;
		}
	}

	cout << dp[n] << "\n";
}