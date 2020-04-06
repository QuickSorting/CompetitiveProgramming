#include <bits/stdc++.h>
 
using namespace std;
 
const int kN = 1e6 + 3;
 
int n, m;
string garden;

int pow2_table[kN];
 
int dp[kN][5];
bool dp_solved[kN][5];

bool illegal[1 << 5];
int new_idx_mask[1 << 5];
 
int get_count(int pos, int mask, int diff){
	if(diff < 0 || diff > 4)
		return 0;
	mask |= 1 << diff;
	if(illegal[mask])
		return 0;
	if(pos == n)
		return 1;

	if(new_idx_mask[mask] >= 3){
		if(diff != new_idx_mask[mask] - 2)
			return pow2_table[(n - pos) / 2];
		return pow2_table[(n - pos + 1) / 2];
	}
	if(new_idx_mask[mask] >= 1){
		int k = (n - pos - 1) / 2;
		if((n - pos - 1) & 1)
			return (pow2_table[k + 1] * 2 - 1) % m;
		return (pow2_table[k] * 3 - 1) % m;
	}
 
	int &ans = dp[pos][diff];
	bool &solved = dp_solved[pos][diff];
	if(solved)
		return ans;
 
	solved = true;
	ans = 0;
 
	ans += get_count(pos + 1, mask, diff + 1);
	ans += get_count(pos + 1, mask, diff - 1);
	while(ans >= m)
		ans -= m;
 
	return ans;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
 
	cin >> n >> m >> garden;

	pow2_table[0] = 1;
	for(int i = 1; i <= n; ++i){
		pow2_table[i] = pow2_table[i - 1] << 1;
		pow2_table[i] = (pow2_table[i] >= m) ? (pow2_table[i] - m) : pow2_table[i];
	}
 
	illegal[(1 << 2)] = true;
	illegal[(1 << 2) + (1 << 1)] = true;
	illegal[(1 << 2) + (1 << 3)] = true;
	illegal[(1 << 2) + (1 << 1) + (1 << 0)] = true;
	illegal[(1 << 2) + (1 << 1) + (1 << 3)] = true;
	illegal[(1 << 2) + (1 << 3) + (1 << 4)] = true;
	

	new_idx_mask[(1 << 2)] = 0;
	new_idx_mask[(1 << 2) + (1 << 1)] = 1;
	new_idx_mask[(1 << 2) + (1 << 3)] = 2;
	new_idx_mask[(1 << 2) + (1 << 1) + (1 << 0)] = 3;
	new_idx_mask[(1 << 2) + (1 << 1) + (1 << 3)] = 4;
	new_idx_mask[(1 << 2) + (1 << 3) + (1 << 4)] = 5;

	for(int i = 0; i < (1 << 5); ++i)
		illegal[i] = !illegal[i];
 
	int ans = 1;
	int mask = (1 << 2), diff = 2;
	for(int i = 0; i < n; ++i){
		if(garden[i] == 'P'){
			ans += get_count(i + 1, mask, diff - 1);
			while(ans >= m)
				ans -= m;
		}
		if(garden[i] == 'L'){
			mask |= 1 << (diff - 1);
			diff -= 1;
		}
		else{
			mask |= 1 << (diff + 1);
			diff += 1;
		}
	}
 
	cout << ans << "\n";
}