#include <bits/stdc++.h>

using namespace std;

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r){
	return mt() % (r - l + 1) + l;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n = rnd(1, 5), m = rnd(1, 7);
	int k = rnd(1, n);

	cout << n << " " << m << " " << k << "\n";
	for(int i = 0; i < n; ++i){
		cout << rnd(1, m) << " " << rnd(1, m) << "\n";
	}
}