#include"holiday.h"
#include <bits/stdc++.h>

using namespace std;

const int kN = 1e5 + 7;
const long long inf = 1e18;

pair<long long, int> nodes[4 * kN];
vector<pair<int, int>> order;
vector<int> idx;

pair<long long, int> merge(pair<long long, int> a, pair<long long, int> b){
	pair<long long, int> ret;
	ret.first = a.first + b.first;
	ret.second = a.second + b.second;
	return ret;
}

void update(int idx, int l, int r, int s, int val){
	if(s < l || r < s)
		return;
	if(l == r){
		nodes[idx].second = val;
		nodes[idx].first = order[l].first * nodes[idx].second;
		return;
	}

	int mid = (l + r) >> 1;
	update(2 * idx, l, mid, s, val);
	update(2 * idx + 1, mid + 1, r, s, val);

	nodes[idx] = merge(nodes[2 * idx], nodes[2 * idx + 1]);
}

pair<long long, int> query(int idx, int l, int r, int cnt){
	if(!cnt)
		return {0, 0};
	if(nodes[idx].second <= cnt)
		return nodes[idx];

	int mid = (l + r) >> 1;
	pair<long long, int> b = query(2 * idx + 1, mid + 1, r, cnt);
	pair<long long, int> a = query(2 * idx, l, mid, cnt - b.second);
	
	return merge(a, b);
}

long long val[3 * kN][2], val_rev[3 * kN][2];

void calc(int l, int r, int sl, int sr, int start, int mul, int n){
	if(l > r)
		return;
	if(sl > sr)
		return;

	int mid = (l + r) >> 1;
	int which = (mul - 1);
	long long best = -inf, best_idx = -1;
	for(int i = sl; i <= sr; ++i){
		update(1, 0, n - 1, idx[i], 1);
		long long rem = mid - (i - start) * mul;
		if(rem < 0)
			break;

		long long curr = query(1, 0, n - 1, rem).first;
		if(curr > best){
			best = curr;
			best_idx = i;
		}
	}
	val[mid][which] = best;

	for(int i = sl; i <= sr; ++i)
		update(1, 0, n - 1, idx[i], 0);

	calc(l, mid - 1, sl, best_idx, start, mul, n);

	for(int i = sl; i < best_idx; ++i)
		update(1, 0, n - 1, idx[i], 1);

	calc(mid + 1, r, best_idx, sr, start, mul, n);

	for(int i = sl; i <= sr; ++i)
		update(1, 0, n - 1, idx[i], 0);
}

void calc_rev(int l, int r, int sl, int sr, int start, int mul, int n){
	if(l > r)
		return;
	if(sl > sr)
		return;

	//cout << "calc_rev " << l << " " << r << " " << sl << " " << sr << " " << start << " " << mul << " " << n << endl; 

	int mid = (l + r) >> 1;
	int which = (mul - 1);
	long long best = -inf, best_idx = -1;
	for(int i = sr; i >= sl; --i){
		update(1, 0, n - 1, idx[i], 1);
		long long rem = mid - (start - i) * mul;
		if(rem < 0)
			break;

		long long curr = query(1, 0, n - 1, rem).first;
		if(curr > best){
			best = curr;
			best_idx = i;
		}
	}
	val_rev[mid][which] = best;

	for(int i = sr; i >= sl; --i)
		update(1, 0, n - 1, idx[i], 0);

	calc_rev(l, mid - 1, best_idx, sr, start, mul, n);
	
	for(int i = sr; i > best_idx; --i)
		update(1, 0, n - 1, idx[i], 1);

	calc_rev(mid + 1, r, sl, best_idx, start, mul, n);

	for(int i = sl; i <= sr; ++i)
		update(1, 0, n - 1, idx[i], 0);
}

long long findMaxAttraction(int n, int start, int d, int attraction[]){
	if(d == 0)
		return 0;
	if(d == 1)
		return attraction[start];
	order.resize(n);
	for(int i = 0; i < n; ++i)
		order[i] = {attraction[i], i};
	sort(order.begin(), order.end());

	idx.resize(n);
	for(int i = 0; i < n; ++i)
		idx[order[i].second] = i;

	calc(0, d, start, n - 1, start, 1, n);
	calc(2, d, start + 1, n - 1, start, 2, n);

	calc_rev(0, d, 0, start, start, 1, n);
	calc_rev(2, d, 0, start - 1, start, 2, n);

	//for(int i = 0; i <= d; ++i)
	//	cout << val[i][0] << " " << val[i][1] << " " << val_rev[i][0] << " " << val_rev[i][1] << " val0 val1 val_rev0 val_rev1" << endl;

	long long ans = 0;
	for(int i = 0; i <= d - 2; ++i)
		ans = max(ans, val[i][0] + val_rev[d - i][1]);
	for(int i = 0; i <= d - 2; ++i)
		ans = max(ans, val_rev[i][0] + val[d - i][1]);

	ans = max(ans, val[d][0]);
	ans = max(ans, val_rev[d][0]);

	return ans;
}
