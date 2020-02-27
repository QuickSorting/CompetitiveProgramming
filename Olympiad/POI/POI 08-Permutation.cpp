/*
	-Followed the given solution
*/
#include <bits/stdc++.h>

using namespace std;

const long long kN = 3e5 + 7;

int max_val = 0;
struct FenwickTree{
	int tr[kN];

	void update(int idx, int diff){
		for(++idx; idx <= max_val; idx += idx & -idx)
			tr[idx] += diff;
	}

	int query(int idx){
		int ret = 0;
		for(++idx; idx >= 1; idx -= idx & -idx)
			ret += tr[idx];
		return ret;
	}

	int query(int l, int r){
		return query(r) - query(l - 1);
	}
};

FenwickTree fenwick;
int cnt_f[kN], n, m, a[kN], idx[kN], idx2[kN];
long long phi;
vector<int> primes, cnt_primes;
long long bare[kN], inv[kN];

long long fast_pow(long long base, long long exp, long long m){
	base %= m;
	long long ret = 1;
	while(exp){
		if(exp & 1)
			ret = (ret * base) % m;
		base = (base * base) % m;
		exp >>= 1;
	}
	return ret;
}

void update_cnt_primes(long long x, int val){
	for(int i = 0; i < primes.size() && x != 1; ++i){
		while(x % primes[i] == 0){
			cnt_primes[i] += val;
			x /= primes[i];
		}
	}
}

void get_bare_and_inv(long long x){
	long long num = x;
	for(long long prime: primes)
		while(num % prime == 0)
			num /= prime; 

	num %= m;
	bare[x] = num;
	inv[x] = fast_pow(num, phi - 1, m);
}

long long get_bare(long long x){
	if(!bare[x])
		get_bare_and_inv(x);
	return bare[x];
}

long long get_inv(long long x){
	if(!inv[x])
		get_bare_and_inv(x);
	return inv[x];
}

void get_primes(){
	int m2 = m;
	for(int d = 2; d * d <= m2; ++d){
		if(m2 % d == 0){
			primes.push_back(d);
			while(m2 % d == 0)
				m2 /= d;
		}
	}
	if(m2 != 1)
		primes.push_back(m2);
	sort(primes.begin(), primes.end());
}

void get_phi(){
	int m2 = m;
	phi = 1;
	for(int prime: primes){
		if(m2 % prime == 0){
			phi *= (prime - 1);
			m2 /= prime;
			while(m2 % prime == 0){
				phi *= prime;
				m2 /= prime;
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	for(int i = 0; i < n; ++i)
		cin >> a[i];

	get_primes();
	cnt_primes.resize(primes.size());

	get_phi();

	set<int> st;
	for(int i = 0; i < n; ++i)
		st.insert(a[i]);

	for(int x: st)
		idx2[x] = max_val++;

	for(int i = 0; i < n; ++i)
		idx[i] = idx2[a[i]];

	long long main_part = 1;
	for(int i = 1; i <= n; ++i){
		main_part *= get_bare(i);
		main_part %= m;
		update_cnt_primes(i, 1);
	}

	for(int i = 0; i < n; ++i){
		fenwick.update(idx[i], 1);
		++cnt_f[idx[i]];
	}

	for(int i = 0; i < max_val; ++i){
		int cnt = fenwick.query(i, i);
		for(int j = 1; j <= cnt; ++j){
			main_part *= get_inv(j);
			main_part %= m;
			update_cnt_primes(j, -1);
		}
	}

	long long ans = 1;
	for(int i = 0; i < n; ++i){
		int cnt = fenwick.query(idx[i] - 1);
		fenwick.update(idx[i], -1);

		main_part *= get_inv(n - i);
		main_part %= m;
		update_cnt_primes(n - i, -1);

		long long curr = main_part;
		if(cnt){
			curr *= get_bare(cnt);
			curr %= m;
			update_cnt_primes(cnt, 1);

			for(int j = 0; j < primes.size(); ++j){
				if(cnt_primes[j]){
					curr *= fast_pow(primes[j], cnt_primes[j], m);
					curr %= m;
				}
			}

			update_cnt_primes(cnt, -1);
			ans += curr;
			while(ans >= m)
				ans -= m;
		}

		main_part *= get_bare(cnt_f[idx[i]]);
		main_part %= m;
		update_cnt_primes(cnt_f[idx[i]], 1);

		--cnt_f[idx[i]];
	}

	cout << ans << "\n";
}