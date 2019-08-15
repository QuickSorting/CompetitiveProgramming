/*followed this solution - http://www.usaco.org/current/data/sol_sort_gold_open18.html*/
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;
const int C = 4;

struct fenwick_tree{
	int arr[N];

	fenwick_tree(){}

	void update(int idx, int val){
		idx += C;

		//cout << "update " << idx << endl;

		for(; idx < N; idx += (idx & -idx)){
			arr[idx] += val;
		}
	}

	int query(int idx){
		idx += C;

		//cout << "query " << idx << endl;

		int ans = 0;
		for(; idx >= 1; idx -= (idx & -idx)){
			ans += arr[idx];
		}

		return ans;
	}

	int query_r(int l, int r){
		return query(r) - query(l - 1);
	}
};

fenwick_tree f;
pair<int, int> a[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);

	int n;

	cin >> n;

	for(int i = 1; i <= n; ++i){
		cin >> a[i].first;
		a[i].second = i;
	}

	sort(a + 1, a + n + 1);

	int ans = 1;

	for(int i = 1; i <= n - 1; ++i){
		int curr = a[i].second;

		f.update(curr, 1);

		int l = i - f.query_r(0, i);

		ans = max(ans, l);
	}

	cout << ans << "\n";

	return 0;
}