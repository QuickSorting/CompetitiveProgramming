#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 7;
vector<int> adj[MAXN];
int n, m;
array<int, 3> nodes[MAXN];
array<int, 4> edges[MAXN];

long long min_distance(const vector<int> &x, const vector<int> &h, const vector<int> &l, const vector<int> &r, const vector<int> &y, int s, int g){
	n = (int)x.size();
	m = (int)l.size();

	for(int i = 0; i < n; ++i)
		nodes[i] = {x[i], h[i], i};
	for(int i = 0; i < m; ++i)
		edges[i] = {y[i], l[i], r[i], i};
	sort(edges, edges + m);
}