#include <bits/stdc++.h>

using namespace std;

vector<long long > m, primes;
long long ans;

set<long long> visited;

void dfs(long long num, bool check){
	visited.insert(num);
	if(check)
		ans = min(ans, num);

	for(long long prime: primes)
		if(num % prime == 0 && !visited.count(num / prime))
			dfs(num / prime, check);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n, k;
	cin >> n >> k;
	ans = n;

	m.resize(k);
	for(int i = 0; i < k; ++i)
		cin >> m[i];
	
	long long n_copy = n;
	for(long long d = 2; d * d <= n_copy; ++d){
		if(n_copy % d == 0){
			primes.push_back(d);
			while(n_copy % d == 0)
				n_copy /= d;
		}
	}
	if(n_copy > 1)
		primes.push_back(n_copy);

	for(int i = 0; i < k; ++i){
		dfs(__gcd(n, m[i]), i == k - 1);
	}

	cout << n / ans << "\n";
}