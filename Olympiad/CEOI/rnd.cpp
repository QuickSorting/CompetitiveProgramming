#include <bits/stdc++.h>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	float f = 0.85;

	float ans = 0.0;
	float curr = 1.0;

	for(int i = 0; i < 10; ++i){
		ans += curr;
		curr += 1.0;
		curr *= f;
	}

	cout << fixed << setprecision(5) << ans << endl;
}