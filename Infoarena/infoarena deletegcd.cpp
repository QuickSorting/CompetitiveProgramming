#include <bits/stdc++.h>

using namespace std;

int next_int(){
	char c;
	do{
		c = getchar();
	}
	while(!isdigit(c));

	int ret = c - '0';
	while(isdigit(c = getchar())){
		ret = 10 * ret + (c - '0');
	}

	return ret;
}

template <typename T>
class fast_vector{
private:
	T arr[10];
	int sz;
public:
	fast_vector(){
		sz = 0;
	}

	bool empty(){
		return (sz == 0);
	}

	int size(){
		return sz;
	}

	void push_back(int value){
		arr[sz++] = value;
	}


	T& operator[](int index){
		return arr[index];
	}
};


const int MAXN = 1e6 + 7;


int n, q, a[MAXN];
int mx[MAXN], mx2[MAXN];
pair<int, int> queries[MAXN];

fast_vector<int> divisors[MAXN];
vector<int> intervals[MAXN];
int pointer[MAXN];

inline int min(int lvalue, int rvalue){
	return ((lvalue < rvalue) ? lvalue : rvalue);
} 

inline int max(int lvalue, int rvalue){
	return ((lvalue > rvalue) ? lvalue : rvalue);
}

void eratosten(){
	for(int i = 2; i < MAXN; ++i){
		if(!divisors[i].empty())
			continue;

		divisors[i].push_back(i);
		for(int j = 2 * i; j < MAXN; j += i){
			divisors[j].push_back(i);
		}
	}
}

void solve(){
	eratosten();

	for(int i = 1; i <= n; ++i){
		for(int j = 0; j < divisors[a[i]].size(); ++j){
			int d = divisors[a[i]][j];

			if(intervals[d].empty()){
				intervals[d].push_back(i);
				continue;
			}

			if(intervals[d].back() == i - 1)
				intervals[d].back() = i;
			else
				intervals[d].push_back(i);
		}
	}

	for(int i = 1; i <= n; ++i){
		mx[i] = mx2[i] = i - 1;
		for(int j = 0; j < divisors[a[i]].size(); ++j){
			int d = divisors[a[i]][j];

			int &p = pointer[d];
			if(intervals[d][p] < i)
				++p;

			mx2[i] = max(mx2[i], intervals[d][p]);
			mx[i] = max(mx[i], min(n, intervals[d][p] + 1));

			if(p + 1 != (int)intervals[d].size()){
				if(a[intervals[d][p] + 2] % d == 0){
					mx[i] = max(mx[i], intervals[d][p + 1]);
				}
			}
		}
	}

	string ans = "";
	for(int i = 0; i < q; ++i){
		int l = queries[i].first, r = queries[i].second;

		if(mx[l] >= r || (l != n && mx2[l + 1] >= r))
			ans += "1";
		else
			ans += "0";
	}
	
	cout << ans << "\n";
}

void read(){
	freopen("deletegcd.in", "r", stdin);
	freopen("deletegcd.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> q;
	for(int i = 1; i <= n; ++i){
		cin >> a[i];
	}
	for(int i = 0; i < q; ++i){
		cin >> queries[i].first >> queries[i].second;
	}
}

int main(){
	read();
	solve();
}