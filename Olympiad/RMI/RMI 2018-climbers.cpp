#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 5007;
const long long inf = 1e18 + 7;

long long a[MAXN], t[MAXN];
long long n;

pair<long long, bool> dp[MAXN][MAXN][2];

long long solve(long long pos1, long long pos2, long long x){
	bool player = (a[pos2] == x);

	if(pos1 == pos2){
		return 0;
	}

	pair<long long, bool> &d = dp[pos1][pos2][player];
	if(d.second){
		return d.first;
	}

	d.second = true;
	d.first = inf;

	if(a[pos1] == a[pos2]){
		if((a[pos1] < a[pos1 + 1]) != (a[pos2 - 1] > a[pos2])){
			return inf;
		}

		int left_dist = abs(a[pos1] - a[pos1 + 1]);
		int right_dist = abs(a[pos2] - a[pos2 - 1]);

		if(left_dist == right_dist){
			d.first = solve(pos1 + 1, pos2 - 1, a[pos1 + 1]);
			return d.first;
		}

		if(left_dist < right_dist){
			d.first = solve(pos1 + 1, pos2, a[pos1 + 1]);
		}
		else{
			d.first = solve(pos1, pos2 - 1, a[pos2 - 1]);
		}
		return d.first;
	}

	if(!player){
		//first
		if(a[pos1] < a[pos1 + 1]){
			d.first = max(d.first, solve(pos1 + 1, pos2, ))
			//if()
		}
		else{
			//a[pos] > a[pos + 1]
		}
	}
	else{
		//second
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("climbers.in", "r", stdin);
	freopen("climbers.out", "w", stdout);

	cin >> n;

	for(long long i = 0; i < n; ++i){
		cin >> a[i];
	}

	long long cnt = 0;
	t[cnt++] = a[0];

	for(long long i = 1; i < n; ++i){
		if(a[i] == t[cnt - 1])
			continue;

		t[cnt++] = a[i];
	}
	n = cnt;
	cnt = 2;

	if(n <= 2){
		if(n == 1){
			cout << "0\n";
			return 0;
		}
		if(n == 2){
			cout << "NO\n";
			return 0;
		}
	}

	a[0] = t[0];
	a[1] = t[1];
	for(long long i = 2; i < n; ++i){
		if((t[i] > a[cnt - 1]) == (a[cnt - 1] > a[cnt - 2])){
			a[cnt - 1] = t[i];
		}
		else{
			a[cnt++] = t[i];
		}
	}
	n = cnt;

	long long ans = solve(0, n - 1, 0);

	if(ans >= inf)
		cout << "NO\n";
	else
		cout << ans << "\n";

	return 0;
}