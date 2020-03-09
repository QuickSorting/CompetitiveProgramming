/*
	-Did the same dp as the other guys
	-Used short to reduce memory
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 2007;

struct MyPair{
	short first;
	bool second;

	MyPair(){
		first = 0;
		second = false;
	}
};

MyPair dp_horizontal[kN][kN], dp_vertical[kN][kN];
long long sum[kN][kN];
int k, n, m;

long long get_sum(int x1, int y1, int x2, int y2){
	long long ret = sum[x2][y2];
	if(x1)
		ret -= sum[x1 - 1][y2];
	if(y1)
		ret -= sum[x2][y1 - 1];
	if(x1 && y1)
		ret += sum[x1 - 1][y1 - 1];

	return ret;
}

short get_dp_horizontal(int x1, int y1, int x2, int y2){
	if(x1 > x2 || y1 > y2)
		return 0;
	if(get_sum(x1, y1, x2, y1) <= k){
		++y1;
		return get_dp_horizontal(x1, y1, x2, y2) + 1;
	}
	if(get_sum(x1, y2, x2, y2) <= k){
		--y2;
		return get_dp_horizontal(x1, y1, x2, y2) + 1;
	}

	if(dp_horizontal[x1][x2].second)
		return dp_horizontal[x1][x2].first;

	dp_horizontal[x1][x2].second = true;
	short &state = dp_horizontal[x1][x2].first;

	state = n + m;
	if(get_sum(x1, y1, x1, y2) <= k)
		state = min<short>(get_dp_horizontal(x1 + 1, y1, x2, y2) + 1, state);
	if(get_sum(x2, y1, x2, y2) <= k)
		state = min<short>(get_dp_horizontal(x1, y1, x2 - 1, y2) + 1, state);
	return state;
}

short get_dp_vertical(int x1, int y1, int x2, int y2){
	if(x1 > x2 || y1 > y2)
		return 0;
	if(get_sum(x1, y1, x1, y2) <= k){
		++x1;
		return get_dp_vertical(x1, y1, x2, y2) + 1;
	}
	if(get_sum(x2, y1, x2, y2) <= k){
		--x2;
		return get_dp_vertical(x1, y1, x2, y2) + 1;
	}

	if(dp_vertical[y1][y2].second)
		return dp_vertical[y1][y2].first;

	dp_vertical[y1][y2].second = true;
	short &state = dp_vertical[y1][y2].first;

	state = n + m;
	if(get_sum(x1, y1, x2, y1) <= k)
		state = min<short>(get_dp_vertical(x1, y1 + 1, x2, y2) + 1, state);
	if(get_sum(x1, y2, x2, y2) <= k)
		state = min<short>(get_dp_vertical(x1, y1, x2, y2 - 1) + 1, state);
	return state;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> k >> n >> m;
	swap(n, m);

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			cin >> sum[i][j];

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(j == 0)
				continue;
			
			sum[i][j] += sum[i][j - 1];
		}
	}
	
	for(int j = 0; j < m; ++j){
		for(int i = 0; i < n; ++i){
			if(i == 0)
				continue;
			
			sum[i][j] += sum[i - 1][j];
		}
	}

	cout << min(get_dp_horizontal(0, 0, n - 1, m - 1), get_dp_vertical(0, 0, n - 1, m - 1)) << "\n";
}