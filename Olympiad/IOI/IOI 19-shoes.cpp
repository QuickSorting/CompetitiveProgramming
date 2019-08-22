#include "shoes.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 7;
const int ADD = 1e5;

int fenwick[MAXN];

void update(int idx, int val){
	for(++idx; idx >= 1; idx -= (idx & -idx)){
		fenwick[idx] += val;
	}
}

int query(int idx){
	int ans = 0;
	for(++idx; idx < MAXN; idx += (idx & -idx)){
		ans += fenwick[idx];
	}

	return ans;
}

queue<int> q[MAXN];
int to[MAXN], from[MAXN];

long long count_swaps(vector<int> s) {
	int n = (int)s.size();

	int cnt = 0;
	for(int i = 0; i < n; ++i){
		if(s[i] < 0){
			if(q[s[i] + ADD].empty()){
				to[i] = cnt * 2;
				q[-s[i] + ADD].push(cnt++);
			}
			else{
				to[i] = q[s[i] + ADD].front() * 2;
				q[s[i] + ADD].pop();
			}
		}
		else{
			if(q[s[i] + ADD].empty()){
				to[i] = cnt * 2 + 1;
				q[-s[i] + ADD].push(cnt++);
			}
			else{
				to[i] = q[s[i] + ADD].front() * 2 + 1;
				q[s[i] + ADD].pop();
			}
		}
	}

	for(int i = 0; i < n; ++i){
		from[to[i]] = i;
	}

	long long ans = 0;

	for(int i = 0; i < n; ++i){
		int curr = query(from[i]) + from[i];
		ans += (long long)abs(curr - i);

		update(from[i], 1);
	}

	return ans;
}
