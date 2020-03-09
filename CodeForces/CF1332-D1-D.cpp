#include <bits/stdc++.h>

using namespace std;

const int kN = 207;

array<int, 2> arr[kN];
int c[kN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;

	for(int j = 0; j < 2; ++j)
		for(int i = 0; i < n; ++i)
			cin >> arr[i][j];

	for(int i = 1; i <= n + m; ++i)
		cin >> c[i];
}