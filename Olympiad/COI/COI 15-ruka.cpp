/*
	I maintain fenwick trees for before and after the current line (for both dimensions).
	Our current line is in before.
	Because we can change only the current line, instead of maintaing the true positions where the lines after are,
		we remain with the previous positions, but instead change where our "zero" is. Here I denote is as add.
	So when we are asked for the current answer we just query 0 for the "before" fenwick tree and add for the "after" fenwick tree.
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 7;

struct fenwick{
	int arr[2 * MAXN];

	fenwick(){}

	void update(int idx, int val){
		idx += MAXN;
		for(; idx < 2 * MAXN; idx += (idx & -idx)){
			arr[idx] += val;
		}
	}

	void update_range(int l, int r, int val){
		if(l > r){
			swap(l, r);
		}
		update(l, val);
		update(r + 1, -val);
	}

	int query(int idx){
		idx += MAXN;
		int ret = 0;
		for(; idx >= 1; idx -= (idx & -idx)){
			ret += arr[idx];
		}
		return ret;
	}
};

int n, m;
array<int, 2> p[MAXN];
array<int, 3> queries[MAXN];
fenwick before[2], after[2];
int add[2];

int get_answer(){
	int ret = 0;
	ret += before[0].query(0);
	ret += before[1].query(0);
	ret += after[0].query(add[0]);
	ret += after[1].query(add[1]);

	return ret;
}

void solve(){
	int sum[2] = {1, 1};
	for(int i = 0; i < 1; ++i){
		for(int j = 0; j < 2; ++j){
			before[j].update_range(sum[j], sum[j] + p[i][j], 1);
			sum[j] += p[i][j];
		}
	}
	for(int i = 1; i < n; ++i){
		for(int j = 0; j < 2; ++j){
			after[j].update_range(sum[j], sum[j] + p[i][j], 1);
			sum[j] += p[i][j];
		}
	}

	sum[0] = 1;
	sum[1] = 1;
	add[0] = 0;
	add[1] = 0;

	int curr_line = 0;
	for(int i = 0; i < m; ++i){
		int type = queries[i][0];

		if(type == 'Q'){
			cout << get_answer() << "\n";
			continue;
		}
		if(type == 'B'){
			if(curr_line != 0){
				for(int j = 0; j < 2; ++j){
					before[j].update_range(sum[j], sum[j] + p[curr_line][j], -1);
					after[j].update_range(sum[j] + add[j], sum[j] + p[curr_line][j] + add[j], 1);
					sum[j] -= p[curr_line - 1][j];
				}
				--curr_line;
			} 
			continue;
		}
		if(type == 'F'){
			if(curr_line != n - 1){
				++curr_line;
				for(int j = 0; j < 2; ++j){
					sum[j] += p[curr_line - 1][j] + add[j];
					after[j].update_range(sum[j], sum[j] + p[curr_line][j], -1);
					sum[j] -= add[j];
					before[j].update_range(sum[j], sum[j] + p[curr_line][j], 1);
				}
			}
			continue;
		}

		//type == 'C'
		for(int j = 0; j < 2; ++j){
			add[j] -= queries[i][j + 1] - p[curr_line][j];
			before[j].update_range(sum[j], sum[j] + p[curr_line][j], -1);
		} 
		p[curr_line] = {queries[i][1], queries[i][2]};
		for(int j = 0; j < 2; ++j){
			before[j].update_range(sum[j], sum[j] + p[curr_line][j], 1);
		}
	}
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> p[i][0] >> p[i][1];
	}

	cin >> m;
	for(int i = 0; i < m; ++i){
		char type;
		cin >> type;

		queries[i][0] = type;
		if(type == 'C'){
			cin >> queries[i][1] >> queries[i][2];
		}
	}
}

int main(){
	read();
	solve();
}