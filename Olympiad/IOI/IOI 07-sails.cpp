/*
	Looked at this - https://github.com/stefdasca/CompetitiveProgramming/blob/6c63b0779a2aa622696573078168727c4379d8f2/IOI/IOI%2007-sails.cpp
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 7;

int fenwick[MAXN];

void update(int idx, int val){
	for(; idx < MAXN; idx += (idx & -idx)){
		fenwick[idx] += val;
	}
}

int query(int idx){
	int ret = 0;

	for(; idx >= 1; idx -= (idx & -idx)){
		ret += fenwick[idx];
	}

	return ret;
}

int n;
pair<int, int> a[MAXN]; //height, number of sails

int binary_search(int val){
	int l = 1, r = MAXN - 4;

	while(l != r){
		int mid = (l + r) >> 1;

		//cout << l << " " << r << endl;

		if(query(mid) > val){
			l = mid + 1;
		}
		else{
			r = mid;
		}
	}

	return l;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for(int i = 0; i < n; ++i){
		cin >> a[i].first >> a[i].second;
	}

	sort(a, a + n);

	

	for(int i = 0; i < n; ++i){
		//cout << i << endl;
		if(a[i].first == a[i].second){
			update(1, 1);
			update(a[i].first + 1, -1);
			continue;
		}

		int val = query(a[i].first - a[i].second + 1);
		//cout << a[i].first << " " << a[i].second << " " << val << endl; 
		int l = binary_search(val), r = min(binary_search(val - 1) - 1, a[i].first);

		//cout << l << "  - " << r << endl;

		update(r + 1, 1);
		update(a[i].first + 1, -1);

		int cnt = r - (a[i].first - a[i].second + 1) + 1;

		update(l, 1);
		update(l + cnt, -1);
	}

	long long ans = 0;

	for(int i = 1; i <= MAXN - 4; i++){
		long long curr = query(i);

		ans += (long long)curr * (curr - 1ll) / 2ll;
	}

	cout << ans << "\n";

	return 0;
}