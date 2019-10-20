/*
	I followed the editorial but couldn't get 75 points with the solution they provided.
	The 100 points one works though.
*/
#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

const int MAXN = 1007;
const int MAXH = 37;

int n, h, p, *a, *b;

int dist[MAXN];
bool used[MAXN];
vector<int> adj[MAXN], adj2[MAXN];
int ans[MAXN][MAXH], par_arr[MAXN];
int add[MAXN];

static void bfs(int from){
	for(int i = 0; i < n; ++i){
		used[i] = false;
	}

	queue<int> q;
	q.push(from);
	dist[from] = 0;
	used[from] = true;

	while(!q.empty()){
		int u = q.front();
		q.pop();

		for(int to: adj2[u]){
			if(!used[to]){
				dist[to] = dist[u] + 1;
				used[to] = true;
				q.push(to);
			}
		}
	}
}

static void output_number(int x){
	for(int i = 0; i < 10; ++i){
		encode_bit((bool)(x & (1 << i))) ;
	}
}

static void dfs(int x){
	used[x] = true;  
	for(int to: adj2[x]){
		if(!used[to]){
			par_arr[to] = x;
			dfs(to);
		}
	}
}

vector<short> v_output;
static void clear_output(){
	short num = 0, power = 1;
	for(short x: v_output){
		num += x * power;
		power *= 3;
	}

	for(short i = 0; i < 5; ++i){
		encode_bit((bool)(num & (1 << i)));
	}
	v_output.clear();
}
static void add_short(short sh){
	v_output.push_back(sh);
	if(v_output.size() == 3){
		clear_output();
	}
}

void encode(int _n, int _h, int _p, int *_a, int *_b){
	n = _n;
	h = _h;
	p = _p;
	a = _a;
	b = _b;

	for(int i = 0; i < p; ++i){
		adj2[a[i]].push_back(b[i]);
		adj2[b[i]].push_back(a[i]);
	}

	for(int i = 0; i < n; ++i){
		used[i] = false;
	}
	dfs(0);
	for(int i = 1; i < n; ++i){
		output_number(par_arr[i]);
	}

	for(int i = 0; i < h; ++i){
		bfs(i);
		for(int j = 1; j < n; ++j){
			if(dist[j] == dist[par_arr[j]]){
				add_short(1);
			}
			else if(dist[j] == dist[par_arr[j]] + 1){
				add_short(2);
			}
			else if(dist[j] == dist[par_arr[j]] - 1){
				add_short(0);
			}
		}
	}
	if(!v_output.empty()){
		clear_output();
	}
}

static int get_input(){
	int ret = 0;
	for(int i = 0; i < 10; ++i){
		if(decode_bit()){
			ret += (1 << i);
		}
	}

	return ret;
}

vector<short> to_get;
static void get_more(){
	short num = 0;
	for(short i = 0; i < 5; ++i){
		num += decode_bit() * (1 << i);
	}
	short power = 9;
	for(short i = 2; i >= 0; --i){
		to_get.push_back(num / power);
		num %= power;
		power /= 3;
	}
}

static short get_short(){
	if(to_get.empty()){
		get_more();
	}

	short ret = to_get.back();
	to_get.pop_back();
	return ret;
}	

static void dfs3(int u, int pr = -1){
	for(int to: adj[u]){
		if(to == pr){
			continue;
		}

		if(to == par_arr[u]){
			dist[to] = dist[u] - add[u];
		}
		else{
			dist[to] = dist[u] + add[to];
		}
		dfs3(to, u);
	}
}

void decode(int _n, int _h){
	n = _n;
	h = _h;

	par_arr[0] = 0;
	for(int i = 1; i < n; ++i){
		par_arr[i] = get_input();
		adj[par_arr[i]].push_back(i);
		adj[i].push_back(par_arr[i]);
	}

	for(int i = 0; i < h; ++i){
		for(int j = 1; j < n; ++j){
			add[j] = get_short() - 1;
		}

		dist[i] = 0;
		dfs3(i);
		for(int j = 0; j < n; ++j){
			ans[j][i] = dist[j];
		}
	}

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < h; ++j){
			hops(j, i, ans[i][j]);
		}
	}
}