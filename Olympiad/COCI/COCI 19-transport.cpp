#include <bits/stdc++.h>

using namespace std;

const int kN = 1e5 + 7;
const int kBIT = 2e5 + 7;

int cnt;
class BinaryIndexedTree{
private:
	int tr[kBIT];

	long long query(int idx){
		long long ans = 0;
		for(; idx >= 1; idx -= idx & -idx)
			ans += tr[idx];
		return ans;
	}
public:
	BinaryIndexedTree(){}
	void update(int idx, int delta){
		for(; idx <= cnt; idx += idx & -idx)
			tr[idx] += delta;
	}
	long long query(int l, int r){
		return query(r) - query(l - 1);
	}
};

struct Edge{
	int to, weight;

	Edge(){}
	Edge(int to, int weight){
		this->to = to;
		this->weight = weight;
	}
};

inline long long min(const long long &a, const long long &b){
	return (a < b ? a : b);
} 

inline long long max(const long long &a, const long long &b){
	return (a > b ? a : b);
} 

int a[kN], subtree_size[kN], n;
vector<Edge> adjacent[kN];
bool visited[kN];
int centroid_decomposition_root;
long long ans = 0;

pair<long long, long long> prefix[kN], suffix[kN];

vector<int> centroid_decomposition[kN];

set<long long> numbers;
map<long long, int> idx;
BinaryIndexedTree fenwick_prefix, fenwick_suffix;

void read_input(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for(int i = 1; i <= n; ++i)
		cin >> a[i];

	for(int i = 0; i < n - 1; ++i){
		int u, v, w;
		cin >> u >> v >> w;

		adjacent[u].push_back(Edge{v, w});
		adjacent[v].push_back(Edge{u, w});
	}
}

void build_subtree_size(int node = 1, int parent = -1){
	subtree_size[node] = 1;
	for(auto [to, weight]: adjacent[node]){
		if(to == parent || visited[to])
			continue;

		build_subtree_size(to, node);
		subtree_size[node] += subtree_size[to];
	}
}

int get_centroid(int node, int parent, const int &component_size){
	for(auto [to, weight]: adjacent[node]){
		if(!visited[to] && to != parent && subtree_size[to] > component_size / 2){
			return get_centroid(to, node, component_size);
		}
	}
	return node;
}

void build_centroid_decomposition(int node = 1, int parent = -1){
	build_subtree_size(node);
	int centroid = get_centroid(node, -1, subtree_size[node]);

	if(parent != -1)
		centroid_decomposition[parent].push_back(centroid);
	else
		centroid_decomposition_root = centroid;

	visited[centroid] = true;
	for(auto [to, weight]: adjacent[centroid]){
		if(!visited[to]){
			build_centroid_decomposition(to, centroid);
		}
	}
	visited[centroid] = false;
}

void build_prefix_and_suffix(int node, int weight_to_parent, int parent){
	suffix[node].first = suffix[parent].first - weight_to_parent + a[node];
	suffix[node].second = min(suffix[parent].first - weight_to_parent, suffix[parent].second);
	prefix[node].first = prefix[parent].first - weight_to_parent + a[node];
	prefix[node].second = min((long long)a[node] - weight_to_parent, a[node] - weight_to_parent + prefix[parent].second);
	prefix[node].second = min(prefix[node].second, 0ll);

	array<long long, 2> v{prefix[node].first, -suffix[node].second};
	for(auto x: v)
		numbers.insert(x);

	for(auto [to, weight]: adjacent[node]){
		if(to == parent || visited[to])
			continue;

		build_prefix_and_suffix(to, weight, node);
	}
}

void get_answer_for_subtree(int node, int parent){
	ans += prefix[node].second >= 0;
	//if prefix can reach to root, adding the a[root] is not necessary
	ans += suffix[node].second >= 0;
	
	if(prefix[node].second >= 0)
		ans += fenwick_suffix.query(1, idx[ prefix[node].first ]);
	ans += fenwick_prefix.query(idx[ -suffix[node].second ], cnt);

	for(auto [to, weight]: adjacent[node]){
		if(to == parent || visited[to])
			continue;
		get_answer_for_subtree(to, node);
	}
}

void add_to_fenwick(int node, int parent, int delta){
	if(prefix[node].second >= 0)
		fenwick_prefix.update(idx[ prefix[node].first ], delta);
	fenwick_suffix.update(idx[ -suffix[node].second ], delta);

	for(auto [to, weight]: adjacent[node]){
		if(to == parent || visited[to])
			continue;

		add_to_fenwick(to, node, delta);
	}
}

void get_answer(int node){
	visited[node] = true;
	prefix[node] = {0, 0};
	suffix[node] = {a[node], 0};

	numbers.clear();
	idx.clear();
	for(auto [to, weight]: adjacent[node]){
		if(visited[to])
			continue;
		build_prefix_and_suffix(to, weight, node);
	}

	cnt = 1;
	for(long long x: numbers)
		idx[x] = cnt++;

	long long ans = 0;
	for(auto [to, weight]: adjacent[node]){
		if(visited[to])
			continue;
		get_answer_for_subtree(to, node);
		add_to_fenwick(to, node, 1);
	}

	for(auto [to, weight]: adjacent[node]){
		if(visited[to])
			continue;
		add_to_fenwick(to, node, -1);
	}

	for(int to: centroid_decomposition[node])
		get_answer(to);
}

int main(){
	read_input();
	build_centroid_decomposition();
	get_answer(centroid_decomposition_root);
	cout << ans << "\n";
}