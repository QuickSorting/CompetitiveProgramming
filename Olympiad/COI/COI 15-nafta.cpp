/*
	-dp[left_drills][position after previous drill]
	-optimized it by divide & conquer approach
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 2007;

template<class T>
void max_check(T &a, const T &b){
	a = a >= b ? a : b;
}

template<class T>
void min_check(T &a, const T &b){
	a = a <= b ? a : b;
}

int r, s;
string land[kN];
bool vis[kN][kN];
vector<array<int, 3>> ranges;

int dp[kN][kN], sum[kN][kN], r_sum[kN], add[kN];

array<int, 3> dfs(int x, int y){
	array<int, 3> ret{y, y, (land[x][y] != '.') ? (land[x][y] - '0') : 0};
	vis[x][y] = true;

	array<pair<int, int>, 4> adj{pair<int, int>{x + 1, y}, {x - 1, y}, {x, y - 1}, {x, y + 1}};
	for(pair<int, int> to: adj){
		if(to.first < 0 || to.first >= r || to.second < 0 || to.second >= s)
			continue;
		if(land[to.first][to.second] == '.' || vis[to.first][to.second])
			continue;

		array<int, 3> curr = dfs(to.first, to.second);
		min_check(ret[0], curr[0]);
		max_check(ret[1], curr[1]);
		ret[2] += curr[2];
	}

	return ret;
}

void solve(int k, int l, int r, int sl, int sr){
	if(l > r)
		return;

	int mid = (l + r) >> 1;

	dp[k][mid] = 0;
	int choice = s;
	for(int nxt = max(mid, sl); nxt <= sr; ++nxt){
		int curr = dp[k - 1][nxt + 1] + sum[mid][nxt];
		if(curr > dp[k][mid]){
			choice = nxt;
			dp[k][mid] = curr;
		}
	}

	solve(k, l, mid - 1, sl, choice);
	solve(k, mid + 1, r, choice, sr);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >> s;
	for(int i = 0; i < r; ++i)
		cin >> land[i];

	for(int i = 0; i < r; ++i)
		for(int j = 0; j < s; ++j)
			if(land[i][j] != '.' && !vis[i][j])
				ranges.push_back(dfs(i, j));

	sort(ranges.begin(), ranges.end());
	for(int i = s - 1, idx = ranges.size() - 1; i >= 0; --i){
		while(idx >= 0 && ranges[idx][0] >= i){
			add[ranges[idx][0]] += ranges[idx][2];
			add[ranges[idx][1] + 1] -= ranges[idx][2];
			--idx;
		}

		int curr_sum = 0;
		for(int j = i; j <= s - 1; ++j){
			curr_sum += add[j];
			sum[i][j] = curr_sum;
			//cout << "sum[" << i << "][" << j << "] = " << sum[i][j] << endl;
		}
	}

	for(int i = 0; i <= s; ++i)
		dp[0][i] = 0;

	for(int k = 1; k <= s; ++k){
		dp[k][s] = 0;

		solve(k, 0, s - 1, 0, s);
	}

	for(int k = 1; k <= s; ++k)
		cout << dp[k][0] << "\n";
}