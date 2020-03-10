#include "gondola.h"
#include <bits/stdc++.h>

using namespace std;

bool check_valid_pair(int lvalue, int rvalue, int n){
	if(lvalue <= 0 || rvalue <= 0)
		return false;
	if(lvalue > n || rvalue > n)
		return true;
	if((lvalue + 1) % n != rvalue % n)
		return false;
	return true;
}

int valid(int n, int inputSeq[]){
	if(n == 1)
		return true;

	for(int i = 0; i < n - 1; ++i)
		if(!check_valid_pair(inputSeq[i], inputSeq[i + 1], n))
			return false;

	if(!check_valid_pair(inputSeq[n - 1], inputSeq[0], n))
		return false;

	sort(inputSeq, inputSeq + n);
	for(int i = 0; i < n - 1; ++i)
		if(inputSeq[i] == inputSeq[i + 1])
			return false;

	return true;
}

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	int start = 0;
	for(int i = 0; i < n; ++i){
		if(gondolaSeq[i] <= n){
			start = i + 1 - gondolaSeq[i];
			if(start < 0)
				start += n;
			break;
		}
	}

	vector<pair<int, int>> v(n);
	for(int i = 0; i < n; ++i)
		v[i] = {gondolaSeq[i], i};
	sort(v.begin(), v.end());

	int cnt_replacement = 0, new_n = n;
	for(int i = 0; i < n; ++i){
		int idx;
		if(v[i].second >= start)
			idx = v[i].second + 1 - start;
		else
			idx = n + v[i].second + 1 - start;

		if(v[i].first > n){
			replacementSeq[cnt_replacement++] = idx;
			++new_n;
			while(v[i].first != new_n){
				replacementSeq[cnt_replacement++] = new_n;
				++new_n;
			}
		}
	}

	return cnt_replacement;
}

const long long mod = 1e9 + 9;

long long fpow(long long base, long long exp){
	if(!exp)
		return 1;
	if(exp & 1)
		return fpow(base, exp ^ 1) * base % mod;

	long long t = fpow(base, exp >> 1);
	return t * t % mod;
}

int countReplacement(int n, int inputSeq[]){
	if(!valid(n, inputSeq))
		return 0;

	int start = 0;
	bool start_exists = false;
	for(int i = 0; i < n; ++i){
		if(inputSeq[i] <= n){
			start = i + 1 - inputSeq[i];
			if(start < 0)
				start += n;
			start_exists = true;
			break;
		}
	}

	int cnt_changed = 0;
	for(int i = 0; i < n; ++i)
		if(inputSeq[i] > n)
			++cnt_changed;

	vector<pair<int, int>> v(n);
	for(int i = 0; i < n; ++i)
		v[i] = {inputSeq[i], i};
	sort(v.begin(), v.end());

	int new_n = n;
	long long ans = 1;
	for(int i = 0; i < n; ++i){
		if(v[i].first > n){
			ans *= fpow(cnt_changed, v[i].first - new_n - 1);
			ans %= mod;
			new_n = v[i].first;
			--cnt_changed;
		}
	}

	if(!start_exists){
		ans *= n;
		ans %= mod;
	}

	return ans;
}
