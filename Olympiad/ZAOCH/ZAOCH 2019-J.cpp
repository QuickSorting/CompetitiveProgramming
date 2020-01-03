#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1007;

int n;
vector<int> adj[MAXN];
bool used[MAXN], in_start_nodes[MAXN];

bool query(const vector<int> &nodes, int l, int r){
	if(nodes.empty())
		return true;

	cout << "? " << r - l + 1;
	for(int i = l; i <= r; ++i)
		cout << " " << nodes[i];
	cout << endl;

	bool ok;
	cin >> ok;
	return ok;
}

void answer(const vector<int> &robbers){
	cout << "! " << (int)robbers.size();
	for(int x: robbers)
		cout << " " << x;
	cout << endl;
}

vector<int> dfs(const vector<int> &start_nodes){
	for(int i = 1; i <= n; ++i)
		used[i] = false;

	queue<int> st;

	for(int u: start_nodes){
		st.push(u);
		used[u] = true;
	}

	vector<int> nodes;
	while(!st.empty()){
		int v = st.front();
		st.pop();

		nodes.push_back(v);
		for(int to: adj[v]){
			if(!used[to]){
				used[to] = true;
				st.push(to); 
			}
		}
	}

	return nodes;
}

bool add(vector<int> &start_nodes, int u, int par = -1){
	if(in_start_nodes[u])
		return true;

	for(int to: adj[u]){
		if(to == par)
			continue;

		if(add(start_nodes, to, u)){
			in_start_nodes[u] = true;
			start_nodes.push_back(u);
			return true;
		}
	}

	return false;
}

void solve(){
	for(int i = 1; i <= n; ++i)
		in_start_nodes[i] = false;

	vector<int> nodes = dfs(vector<int>{1});

	int l = 0, r = n - 1;
	while(l != r){
		int mid = (l + r + 1) >> 1;
		if(query(nodes, 0, mid - 1))
			r = mid - 1;
		else
			l = mid;
	}

	vector<int> robbers{nodes[l]}, start_nodes{nodes[l]};
	in_start_nodes[nodes[l]] = true;
	while((int)robbers.size() < 10){
		nodes = dfs(start_nodes);

		l = 0, r = n - 1;
		while(l != r){
			int mid = (l + r + 1) >> 1;
			if(query(nodes, 0, mid - 1))
				r = mid - 1;
			else
				l = mid;
		}

		if(l < (int)start_nodes.size())
			break;

		robbers.push_back(nodes[l]);
		add(start_nodes, nodes[l]);
	}
	answer(robbers);
}

void read(){
	cin >> n;
	for(int i = 0; i < n - 1; ++i){
		int u, v;
		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

int main(){
	read();
	while(true){
		string s;
		cin >> s;
		if(s == "E")
			break;

		solve();
	}
}