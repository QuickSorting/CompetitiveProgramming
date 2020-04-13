/*
	Solved by divide & conquer optimization
*/
#include <bits/stdc++.h>

using namespace std;

const int k_N = 1000 + 3;
const long long k_Inf = 1e18;
const int k_K = 7 + 3;

int n, k;
int r[k_N];
long long dp[k_K][k_N];
long long prefix_incr[k_N], prefix_one[k_N];

long long get_sum(int l, int r){
	return (prefix_incr[r] - prefix_incr[l - 1]) - (prefix_one[r] - prefix_one[l - 1]) * l;
}

void divide_and_conquer(int l, int r, int sl, int sr, int start, int k_idx){
	if(l > r)
		return;

	int mid = (l + r) >> 1;
	int chosen_idx = max(sl, mid);
	long long chosen_score = get_sum(mid, chosen_idx) + dp[k_idx - 1][chosen_idx + 1];
	for(int i = max(sl, mid); i <= sr; ++i){
		long long curr_score = get_sum(mid, i) + dp[k_idx - 1][i + 1];
		if(curr_score < chosen_score){
			chosen_score = curr_score;
			chosen_idx = i;
		} 
	}

	dp[k_idx][mid] = chosen_score;

	divide_and_conquer(l, mid - 1, sl, chosen_idx, start, k_idx);
	divide_and_conquer(mid + 1, r, chosen_idx, sr, start, k_idx);
}

long long get_answer_with_start(int start){
	for(int i = 1; i <= n; ++i){
		int curr = (i + start - 2) % n + 1; 
		prefix_one[i] = prefix_one[i - 1] + r[curr];
		prefix_incr[i] = prefix_incr[i - 1] + r[curr] * i;
	}

	for(int i = 1; i <= n; ++i)
		dp[0][i] = k_Inf;
	dp[0][n + 1] = 0;

	for(int k_idx = 1; k_idx <= k; ++k_idx){
		divide_and_conquer(1, n, 1, n, start, k_idx);
		dp[k_idx][n + 1] = 0;
	}

	return dp[k][1];
}

long long get_answer(){
	long long answer = k_Inf;
	for(int i = 1; i <= n; ++i)
		answer = min(answer, get_answer_with_start(i));
	return answer;
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("cbarn.in", "r", stdin);
	freopen("cbarn.out", "w", stdout);

	cin >> n >> k;
	for(int i = 1; i <= n; ++i)
		cin >> r[i];
}

int main(){
	read();
	cout << get_answer() << "\n";
}