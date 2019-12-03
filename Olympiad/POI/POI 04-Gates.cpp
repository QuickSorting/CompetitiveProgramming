/*
	-Followed the tutorial
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 7;

int n, ans[MAXN][2], sum[MAXN];
vector<int> adj[MAXN], r_adj[MAXN];
int add[3] = {-1, 1, 0};
bool in_queue[MAXN];

int find_need(int u){
	int need;
	if(sum[u] == 0)
		need = 2;
	else if(sum[u] > 0)
		need = 1;
	else
		need = 0;

	return need;
}

void fill(bool val){
	for(int i = 2; i < n; ++i){
		ans[i][val] = val;
		sum[i] = 0;
	}
	ans[0][val] = 0;
	ans[1][val] = 1;
	sum[0] = -1;
	sum[1] = 1;

	queue<int> q;
	for(int u = 2; u < n; ++u){
		q.push(u);
		in_queue[u] = true;
		for(int to: r_adj[u]){
			sum[u] += add[ans[to][val]];
		}
	}

	while(!q.empty()){
		int u = q.front();
		q.pop();
		in_queue[u] = false;

		int need = find_need(u);
		if(need == ans[u][val])
			continue;

		
		for(int to: adj[u]){
			sum[to] -= add[ans[u][val]];
			sum[to] += add[need];

			if(find_need(to) != ans[to][val] && !in_queue[to]){
				q.push(to);
				in_queue[to] = true;
			}
		}
		ans[u][val] = need;
	}
}

void solve(){
	fill(0);
	fill(1);
}

void write(){
	for(int i = 0; i < n; ++i){
		if(ans[i][0] != ans[i][1])
			cout << "?\n";
		else if(ans[i][0] == 2)
			cout << "1/2\n";
		else
			cout << ans[i][0] << "\n";
	}
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int u = 2; u < n; ++u){
		int k;
		cin >> k;

		for(int j = 0; j < k; ++j){
			int par;
			cin >> par;

			adj[par].push_back(u);
			r_adj[u].push_back(par);
		}
	}
}

int main(){
	read();
	solve();
	write();
}