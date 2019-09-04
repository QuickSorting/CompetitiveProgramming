/*
	not working
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 8;
const int MAXP = 1e3 + 250;
const long double inf = 1e9 + 7;
const long double eps = 1e-10;

int primes[MAXP];
int cnt_p = 0;
long double dp[MAXN][2], lg_pr[MAXP];
vector<int> nums[MAXN][2];

bool better(long double pr, long double nxt){
	return (long double)nxt - pr > (long double)eps;
}

void calc_primes(){
	for(int i = 2; i <= 9007; ++i){
		bool ok = true;
		for(int j = 2; j * j <= i; ++j){
			if(i % j){
				continue;
			}
			ok = false;
			break;
		}
		if(ok){
			lg_pr[cnt_p] = (long double)log(i);
			primes[cnt_p++] = i;
		}
	}
	cout << cnt_p << endl;
}

long double precompute(){
	for(int pos = cnt_p - 1; pos >= 0; --pos){
		int curr = pos & 1, nxt = (pos + 1) & 1; 

		for(int left = 0; left <= 1000; ++left){
			if(primes[pos] > left){
				dp[left][curr] = (long double)0.0;
				continue;
			}

			dp[left][curr] = dp[left - 1][curr];
			nums[left][curr] = nums[left - 1][curr];
			nums[left][curr].push_back(1);

			long double take = dp[left - primes[pos]][nxt] + lg_pr[pos];
			if(better(dp[left][curr], take)){
				dp[left][curr] = take;
				nums[left][curr] = nums[left - primes[pos]][nxt];
				nums[left][curr].push_back(primes[pos]);
			}

			take = dp[left][nxt];
			if(better(dp[left][curr], take)){
				dp[left][curr] = take;
				nums[left][curr] = nums[left][nxt];
			}
			cout << nums[left][curr].size() << " - " << left << " " << curr << endl;
			cout << dp[left][curr] << endl << endl;
 		}
	}
}

vector<int> ans;

void solve(){
	int n;

	cin >> n;

	if(n <= 4){
		for(int i = 2; i <= n; ++i){
			cout << i << " ";
		}
		cout << 1 << "\n";
		return;
	}

	long double f1 = dp[n][0];
	long double f2 = dp[n - 4][1] + (long double)log(4.0);

	if(better(f2, f1)){
		ans = nums[n][0];  
	}
	else{
		ans = nums[n - 4][1];
		ans.push_back(4);
	}
	sort(ans.begin(), ans.end());
	
	int curr = 1;
	for(int i = 0; i < ans.size(); ++i){
		for(int j = 1; j < ans[i]; ++j){
			cout << curr + j << " ";
		}
		cout << curr << " ";
		curr += ans[i];
	}
	cout << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int q;
	calc_primes();
	precompute();
	return 0;

	cin >> q;

	while(q--){
		solve();
	}

	return 0;
}