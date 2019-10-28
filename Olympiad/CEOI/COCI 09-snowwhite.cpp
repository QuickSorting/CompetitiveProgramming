/*
	I use Mo's algorithm.
	I am maintaining:
	- the number of people with each color - in cnt
	- the xor of the colors with the same count - in cnt2
	- the number of colors with the same count - in cnt3
	Because we want to know the color only if it's the one with the biggest count
	the count will be 1 so the xor will be the number.
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 7;
const int MAXC = 1e4 + 7;

const int X = 1000;

int n, c, m;
array<int, 3> quer[MAXN];
int a[MAXN], cnt[MAXC], big, val_big;
int ans[MAXN], cnt2[MAXN], cnt3[MAXN];

bool cmp(array<int, 3> lvalue, array<int, 3> rvalue){
	if(lvalue[0] / X != rvalue[0] / X){
		return lvalue[0] < rvalue[0];
	}
	return ((lvalue[0] / X) & 1) ? (lvalue[1] < rvalue[1]) : (lvalue[1] > rvalue[1]);
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> c;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}
	cin >> m;
	for(int i = 0; i < m; ++i){
		cin >> quer[i][0] >> quer[i][1];
		--quer[i][0];
		--quer[i][1];
		quer[i][2] = i;
	}
}

void add(int idx){
	++cnt[a[idx]];
	cnt2[ cnt[a[idx]] - 1 ] ^= a[idx];
	--cnt3[ cnt[a[idx]] - 1 ];
	cnt2[ cnt[a[idx]] ] ^= a[idx];
	++cnt3[ cnt[a[idx]] ];
	if(cnt[a[idx]] > big){
		++big;
	}
}

void rem(int idx){
	--cnt[a[idx]];
	cnt2[ cnt[a[idx]] + 1 ] ^= a[idx];
	--cnt3[ cnt[a[idx]] + 1];
	cnt2[ cnt[a[idx]] ] ^= a[idx];
	++cnt3[ cnt[a[idx] ]];
	if(big == cnt[a[idx]] + 1 && !cnt3[ cnt[a[idx]] + 1]){
		--big;
	}
}

void solve(){
	sort(quer, quer + m, cmp);

	for(int i = 1; i <= c; ++i){
		cnt2[0] ^= i;
	}

	big = 0;
	int l = 0, r = -1;
	for(int i = 0; i < m; ++i){
		for(int j = r + 1; j <= quer[i][1]; ++j){
			add(j);
		}
		for(int j = l - 1; j >= quer[i][0]; --j){
			add(j);
		}

		for(int j = r; j > quer[i][1]; --j){
			rem(j);
		}
		for(int j = l; j < quer[i][0]; ++j){
			rem(j);
		}

		l = quer[i][0];
		r = quer[i][1];
		if(2 * big > r - l + 1){
			ans[ quer[i][2] ] = cnt2[big];
		}
		else{
			ans[quer[i][2]] = -1;
		}
	}

	for(int i = 0; i < m; ++i){
		if(ans[i] == -1){
			cout << "no\n";
		}
		else{
			cout << "yes " << ans[i] << "\n";
		}
	}
}

int main(){
	read();
	solve();
}