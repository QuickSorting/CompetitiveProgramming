/*
	Followed tmw's solution
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e6 + 7;
void calc_l_r();

int n, l[MAXN], r[MAXN], idx[MAXN];
long long a[MAXN];
vector<int> group[2 * MAXN];
set<int> curr;
set<pair<int, int> > set2;

void solve(){
	calc_l_r();
	for(int i = 1; i <= n; ++i){
		group[MAXN + a[i] - i].push_back(i);
	}

	for(int i = 0; i < 2 * MAXN; ++i){
		if(group[i].empty()){
			continue;
		}

		curr.clear();
		set2.clear();
		for(int j = 0; j < (int)group[i].size(); ++j){
			int x = group[i][j];

			while(!set2.empty()){
				if(set2.begin()->first <= x){
					curr.erase(set2.begin()->second);
					set2.erase(set2.begin());
				}
				else{
					break;
				}
			}

			if(!curr.empty() && l[x] < *curr.rbegin()){
				idx[x] = *curr.rbegin();
			}
 
			curr.insert(x);
			set2.insert({r[x], x});
		}
	}

	vector<pair<int, int> > ans;
	stack<int> st;
	for(int i = n; i >= 1; --i){
		if(!idx[i]){
			continue;
		}
		while(!st.empty() && idx[st.top()] <= idx[i]){
			idx[st.top()] = 0;
			st.pop();
		}
		st.push(i);
	}

	for(int i = 1; i <= n; ++i){
		if(idx[i]){
			ans.push_back({idx[i], i});
		}
	}

	cout << (int)ans.size() << "\n";
	for(pair<int, int> p: ans){
		cout << p.first << " " << p.second << "\n";
	}
}

void calc_l_r(){
	stack<int> st;

	for(int i = 1; i <= n; ++i){
		while(!st.empty() && a[i] < a[st.top()]){
			r[st.top()] = i;
			st.pop(); 
		}
		st.push(i);
	}
	while(!st.empty()){
		r[st.top()] = n + 1;
		st.pop();
	}

	for(int i = n; i >= 1; --i){
		while(!st.empty() && a[i] > a[st.top()]){
			l[st.top()] = i;
			st.pop();
		}
		st.push(i);
	}
	while(!st.empty()){
		l[st.top()] = 0;
		st.pop();
	}
}

void read(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
	}
}

int main(){
	read();
	solve();
}