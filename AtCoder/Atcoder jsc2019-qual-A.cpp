#include <bits/stdc++.h>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int m, d;

	cin >> m >> d;

	int ans = 0;

	for(int i = 1; i <= m; ++i){
		for(int j = 20; j <= d; ++j){
			if((j % 10) < 2){
				continue;
			}

			if((j % 10) * (j / 10) == i){
				++ans;
				//cout << j << " " << i << endl;
			}
		}
	}

	cout << ans << "\n";
	
	return 0;
}