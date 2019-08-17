/*
	Implemented this - http://www.boi2011.ro/resurse/tasks/trapezoid-sol.pdf
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 7;
const int mod = 30013;
const int inf = 1e9;

struct line{
	int first, second, idx;
	bool type;

	line(){}
};

bool cmp(line lvalue, line rvalue){
	return lvalue.first < rvalue.first;
}

struct fenwick_tree{
	pair<int, int> arr[MAXN];

	fenwick_tree(){
		for(int i = 0; i < MAXN; ++i){
			arr[i] = {0, 0};
		}
	}

	void update(int idx, pair<int, int> val){
		for(; idx < MAXN; idx += (idx & -idx)){
			if(val.first > arr[idx].first){
				arr[idx] = val;
			}
			else{
				if(val.first == arr[idx].first){
					arr[idx].second += val.second;
					arr[idx].second %= mod;
				}
			}
		}
	}

	pair<int, int> query(int idx){
		pair<int, int> ans = {1, 1};
		for(; idx >= 1; idx -= (idx & -idx)){
			if(arr[idx].first + 1 > ans.first){
				ans = {arr[idx].first + 1, max(arr[idx].second, 1)};
			}
			else{
				if(arr[idx].first + 1 == ans.first){
					ans.second += arr[idx].second;
					ans.second  %=  mod;
				}
			}
		}

		return ans;
	}
};

fenwick_tree f;

pair<int, int> dp[MAXN];
line t[MAXN];
set<int> st;
map<int, int> mp;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;

	cin >> n;

	for(int i = 0; i < n; ++i){
		cin >> t[2 * i].first >> t[2 * i + 1].first >> t[2 * i].second >> t[2 * i + 1].second;
		st.insert(t[2 * i].second);
		st.insert(t[2 * i + 1].second);
	}

	int cnt = 1;
	for(int x: st){
		mp[x] = cnt++; 
	}

	for(int i = 0; i < 2 * n; i++){
		t[i].second = mp[t[i].second];
	}

	t[2 * n].first = inf;
	t[2 * n + 1].first = inf + 1;
	t[2 * n].second = 2 * n + 1;
	t[2 * n + 1].second = 2 * n + 2;

	for(int i = 0; i < 2 * n + 2; ++i){
		if(i & 1){
			t[i].type = false;
		}
		else{
			t[i].type = true;
		}
		t[i].idx = i / 2;
	}

	sort(t, t + 2 * n + 2, cmp);
	for(int i = 0; i < 2 * n + 2; ++i){
		if(t[i].type){
			dp[t[i].idx] = f.query(t[i].second);
			//cout << i << " iiii " << dp[cnt1 - 1].first << " " << dp[cnt1 - 1].second << " - " << cnt1 - 1 << endl;
		}
		else{
			//cout << "update " << t[i].second << " " << dp[cnt2].first << "," << dp[cnt2].second << endl;
			f.update(t[i].second, dp[t[i].idx]);
		}	
	}

	cout << dp[n].first - 1 << " " << dp[n].second << "\n";

	return 0;
}