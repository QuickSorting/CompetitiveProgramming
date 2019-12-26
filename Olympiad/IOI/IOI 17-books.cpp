#include <bits/stdc++.h>
#include "books.h"

using namespace std;

const long long inf = 1e18;

long long bfs(int from, 
             int to, 
             const int &n, 
             const vector<pair<int, int> > &range){
	vector<bool> used(n, false);
	vector<long long> dist(n);
	deque<int> q;

	for(int i = 0; i < n; ++i)
		dist[i] = inf;

	q.push_back(from);
	dist[from] = 0;

	int l = from, r = from;
	while(!q.empty()){
		int u = q.front();
		q.pop_front();

		if(u == to)
			return dist[to];
		if(used[u])
			continue;
		used[u] = true;
		r = max(r, u);
		l = min(l, u);
	
		if(range[u].first < l){
			for(int i = range[u].first; i < l; ++i){
				if(used[i])
					continue;

				q.push_front(i);
				dist[i] = dist[u];
			}
			l = range[u].first;
		}
		if(range[u].second > r){
			for(int i = r + 1; i <= range[u].second; ++i){
				if(used[i])
					continue;

				q.push_front(i);
				dist[i] = dist[u];
			}
			r = range[u].second;
		}

		if(u + 1 < n && dist[u + 1] > dist[u] + 1){
			dist[u + 1] = dist[u] + 1;
			q.push_back(u + 1);
		}
		if(range[u].first - 1 >= 0 && dist[u - 1] > dist[u] + 1){
			dist[u - 1] = dist[u] + 1;
			q.push_back(u - 1);
		}
	}

	return inf;
}

long long minimum_walk(vector<int> p, int s) {
	int n = (int)p.size();
	vector<int> rev(n);
	vector<pair<int, int> > range(n);
	long long ans = 0;

	for(int i = 0; i < n; ++i){
		rev[p[i]] = i;
		range[i] = {i, i};
	}

	int l = s, r = s;
	for(int i = 0; i < n; ++i){
		if(p[i] != i){
			l = min(l, i);
			r = max(r, i);
		}
	}

	for(int i = 0; i < n; ++i){
		if(p[i] != i){
			vector<int> cycle;

			int v = i;
			do{
				ans += abs(p[v] - v);
				cycle.push_back(v);

				int prev = v;
				v = p[v];
				p[prev] = prev;
			}
			while(v != i);

			int l_cycle = cycle[0], r_cycle = cycle[0];
			for(int x: cycle){
				l_cycle = min(l_cycle, x);
				r_cycle = max(r_cycle, x);
			}

			for(int x: cycle)
				range[x] = {l_cycle, r_cycle};
		}
	}

	long long l_ans = bfs(s, l, n, range);
	long long r_ans = bfs(s, r, n, range);

	ans += r_ans + l_ans + bfs(l, r, n, range);

	return ans;
}
