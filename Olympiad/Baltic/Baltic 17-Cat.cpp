/*
	The idea is to solve almost like a dp.

	We want to find the answer for every subtree if we cared only about it.

	If we have the answers for all children of the current node, then we know that
	the only nodes that we may have to be unmarked are the ones that are the closest to the current
	root. So we can add those nodes subtree by subtree from the ones that are furthest away
	and if at some point the nodes would be too close to the nodes of the other subtrees, we stop.

	Also, we don't really need to store the count of closest nodes because if there is more than one
	node with the same distance to the current root, then because the distance between any two of them is >= d,
	so their depth is >= (d / 2). That means it for sure is included in the answer. So the removed nodes will only be at most
	1 per subtree.

	O(nlogn)
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 2e5 + 7;

int n, d;
int min_dist[kN], subtree_depth[kN];
vector<int> adjacent[kN];

int dfs(int u, int dist){
	int answer = 0;

	for(int to: adjacent[u])
		answer += dfs(to, dist + 1);
	answer -= adjacent[u].size();
	sort(adjacent[u].begin(), adjacent[u].end(), [](const int &lvalue, const int &rvalue){
		return min_dist[lvalue] > min_dist[rvalue];
	});

	int curr_min_dist = dist;
	for(int to: adjacent[u]){
		if(curr_min_dist + min_dist[to] + 1 >= d){
			++answer;
			curr_min_dist = min(curr_min_dist, min_dist[to] + 1);
			dist = min(dist, min_dist[to] + 1);
		}
		else
			break;
	}

	if(dist >= d){
		dist = 0;
		++answer;
	}

	min_dist[u] = dist;
	return answer;
}

void build_subtree_depth(int u, int depth){
	subtree_depth[u] = depth;
	for(int to: adjacent[u]){
		build_subtree_depth(to, depth + 1);
		subtree_depth[u] = max(subtree_depth[to], subtree_depth[u]);
	}
}

int get_answer(){
	build_subtree_depth(0, 0);
	return dfs(0, d);
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> d;
	for(int node = 1; node < n; ++node){
		int parent;
		cin >> parent;

		adjacent[parent].push_back(node);
	}
}

int main(){
	read();
	cout << get_answer() << "\n";
}