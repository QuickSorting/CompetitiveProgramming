#include <bits/stdc++.h>

using namespace std;

struct point{
	int x, y;
	point(){}
	point(int x, int y):x(x),y(y){}
};

const int inf = 1e9;

inline int sq(int x){
	return x * x;
}
int dist(point a, point b)

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;

	int cnt_frogs;
	cin >> cnt_frogs;

	vector<point> frogs;
	for(int i = 0; i < cnt_frogs; ++i){
		int x, y;
		cin >> x >> y;
		frogs.push_back(point(x, y));
	}

	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j){
			int curr = inf;
		}
	}
}