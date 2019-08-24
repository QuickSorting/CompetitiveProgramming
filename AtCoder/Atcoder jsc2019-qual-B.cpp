#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 7;
const long long mod = 1e9 + 7;

long long a[MAXN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n, k;

	cin >> n >> k;

	for(int i = 0; i < n; ++i){
		cin >> a[i];
	}

	long long ans = 0;

	for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n; ++j){
			if(a[i] > a[j]){
				++ans;
			}
		}
	}

	ans *= k;
	ans %= mod;

	long long ans2 = 0;

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(a[i] > a[j]){
				++ans2;
			}
		}
	}

	ans2 *= (k * (k - 1ll) / 2ll) % mod;
	ans2 %= mod;

	cout << (ans + ans2) % mod << "\n";

	return 0;
}