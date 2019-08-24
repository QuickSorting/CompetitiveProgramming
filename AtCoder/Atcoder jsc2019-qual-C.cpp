#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 7;
const long long mod = 1e9 + 7;

string s;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	long long n;

	cin >> n >> s;

	n = 2ll * n;

	long long ans = 1ll;
	long long l = 0;
	bool w = false;
	char pr = 'W';

	for(int i = 0; i < n; ++i){
		if(s[i] == pr){
			w = !w;
		}
		pr = s[i];

		if(!w){
			++l;
		}
		else{
			if(!l){
				cout << "0\n";

				return 0;
			}
			ans *= l;
			ans %= mod;
			--l;
		}
	}
	if(l > 0){
		cout << "0\n";

		return 0;
	}

	for(long long i = (n / 2ll); i >= 1ll; --i){
		ans *= i;
		ans %= mod;
	}

	cout << ans << "\n";

	return 0;
}