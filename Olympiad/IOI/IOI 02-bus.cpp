/* 
	-Copied solution
*/
#include <bits/stdc++.h>

using namespace std;

const int kN = 507;
const int kInf = 1e9;

int x[kN], y[kN], dist[kN][kN], idx[kN];

int q;
bool cmp(int lvalue, int rvalue){
	return dist[lvalue][q] > dist[rvalue][q];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, ans = kInf;
	cin >> n;

	for(int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];

	for(int i = 0; i < n; ++i)
		idx[i] = i;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			dist[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);

	for(int i = 0; i < n; ++i){
		q = i;
		sort(idx, idx + n, cmp);

		for(int j = 0; j < n; ++j){
			int low = 0;
			for(int k = 0; k < n; ++k)
				if(dist[idx[low]][j] < dist[idx[k]][j])
					ans = min(ans, dist[i][j] + dist[idx[low]][j] + dist[idx[k]][i]), low = k;
		} 
	}

	cout << ans << "\n";
}