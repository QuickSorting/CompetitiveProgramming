#include <bits/stdc++.h>

using namespace std;

void solve(){
	long long p, q, a, b, n;
	cin >> p >> q >> a >> b >> n;

	if(a == 0){
		if(n == 0)
			cout << "Yes\n";
		else
			cout << "No\n";
		return;
	}

	if(n % p){
		cout << "No\n";
		return;
	}
	n /= p;

	if(a > n){
		cout << "No\n";
		return;
	}

	long long power = 1;
	if(q != 1){
		for(long long i = 0; i < b; ++i, power *= q){
			if(make_pair(power, 0ll) > make_pair(n / q, n % q))
				break;
		}
	}

	long long sum = 0;
	while(n){
		sum += n / power;
		n %= power;
		power /= q;
	}

	if(q == 1){
		if(sum == a)
			cout << "Yes\n";
		else
			cout << "No\n";
		return;
	}

	if(sum > a || sum % (q - 1) != a % (q - 1)){
		cout << "No\n";
		return;
	}
	cout << "Yes\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;

	while(t--)
		solve();
}