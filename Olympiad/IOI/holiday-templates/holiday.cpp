#include"holiday.h"
#include <bits/stdc++.h>

using namespace std;

const int kN = 1e5 + 7;

pair<long long, int> nodes[4 * kN];
vector<pair<int, int>> order;

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

long long findMaxAttraction(int n, int start, int d, int attraction[]){
	order.resize(n);
	for(int i = 0; i < n; ++i)
		order[i] = {attraction[i], i};
	sort(order.begin(), order.end());

	vector<int> idx(n);
	for(int i = 0; i < n; ++i)
		idx[order[i].second] = i;

	long long ans = 0;
	for(int i = start; i >= 0; --i){
		update(1, 0, n - 1, idx[i], 1);
		for(int j = start + 1; j < n; ++j)
			update(1, 0, n - 1, idx[j], 0);
		for(int j = start; j < n; ++j){
			update(1, 0, n - 1, idx[j], 1);
			int dist = min(start - i, j - start) * 2 + max(start - i, j - start);
			if(dist > d)
				break;

			ans = max(query(1, 0, n - 1, d - dist).first, ans);
		}
	}
	return ans;
}
