	#include <bits/stdc++.h>

	using namespace std;

	int main(){
		ios::sync_with_stdio(false);
		cin.tie(NULL);

		int n;

		cin >> n;

		for(int i = 1; i <= n; ++i){
			for(int j = i + 1; j <= n; ++j){
				for(int idx = 0; true; ++idx){
					if((i & (1 << idx)) != (j & (1 << idx))){
						cout << idx + 1 << " ";
						break;
					}
				}
			}
			cout << "\n";
		}

		return 0;
	}